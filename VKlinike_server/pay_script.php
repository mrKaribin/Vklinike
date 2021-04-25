<?php

    $debug = FALSE;
    $sandbox = TRUE;
    
    function send_request($ch, $debug = false, $crash = true)
    {
        if($debug === TRUE){
            echo "\n\nDEBUGER {\n";
            //curl_setopt($ch, CURLOPT_VERBOSE, TRUE);
        }
        $buffer = curl_exec($ch);
        curl_close($ch);
        if($buffer === FALSE)
        {
            if($crash === TRUE){
                exit("\n" . 'Request error: ' . curl_error($ch));}
            else{
                echo "\n" . 'Request error: ' . curl_error($ch);}
        }
        else
        {
            if($debug === TRUE)
            {
                echo "\n" . 'Reply: ' . $buffer . "\n}";
            }
            return json_decode($buffer);
        }
    }   
    
    if($argc > 1)
    {
        $sys_login = $argv[1];
    }
    else
    {
        if($sandbox === TRUE)
        {
            $sys_login = 'AYqpHUh16DjPqiVKIKLF-TK-jWVqf7jp_0vd-BRgGT8qOzVh_IKHn9LJ9c6PrGQWGekw_XHSdV1SPwAC';
        }
        else
        {
            $sys_login = 'Aa76WqBVOPtSu21aVR1UKkvZJJkTThZCe06XsBu_W8iQr6ypM3b4Acshh6nRx_LOUYjOijnn2fwHxh8A';
        }
    }
    
    if($argc > 2)
    {
        $sys_pass = $argv[2];
    }
    else
    {
        if($sandbox === TRUE)
        {
            $sys_pass = 'EHmL4TGXBuu5aal2jEeIepKzWXVkuTh2GnU34uKwFmUhRn0AWpUIpPDwZRheI34J8mpTUgjidVhYcAl1';
        }
        else
        {
            $sys_pass = 'EFAkayHZip25tGrabslsXss-3asQ2MDxMJJryaseXBVO00ILPhGosXkRnDPYcK8-RvI4YprxlunG5FmK';
        }
    }
    
    if($argc > 3)
    {
        $valuta = $argv[3];
    }
    else
    {
        $valuta = 'RUB';
    }

    if($argc > 4)
    {
        $cost = $argv[4];
    }
    else
    {
        $cost = 1500;
    }

    if($argc > 5)
    {
        $pay_id = $argv[5];
    }
    
    if($sandbox === TRUE)
    {
        $home = 'https://api.sandbox.paypal.com'; 
    }
    else
    {
        $home = 'https://api.paypal.com';    
    }
    
    echo "\n\nInitial data:\naccount: " . $sys_login;
    echo "\npassword: " . $sys_pass;
    echo "\nvaluta: " . $valuta;
    echo "\ncost: " . $cost;
    
    $url = $home . '/v1/oauth2/token';
    $ch = curl_init($url);
    curl_setopt_array($ch, array(
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_HTTPHEADER => array(
            'Accept: application/json',
            'Accept-Language: en_US'
        ),
        CURLOPT_USERPWD => $sys_login . ':' . $sys_pass,
        CURLOPT_POST => 1,
        CURLOPT_POSTFIELDS => 'grant_type=client_credentials',
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_SSL_VERIFYPEER => FALSE,
    ));
    
    $response = send_request($ch, $debug);
    $token = "$response->access_token";
    echo "\n\nAutorization successful\nAccess_token: " . $token;
    
    $url = $home . '/v2/checkout/orders';
    $postfields = json_encode(array(
            'intent' => 'CAPTURE',
            'purchase_units' => array(array(
                'amount' => array(
                    'currency_code' => $valuta,
                    'value'         => $cost
                )
            )),
            'order_application_context' => array(
                'return_url' => 'https://yandex.ru',
                'cancel_url' => 'https://google.com'
            )
        ), JSON_UNESCAPED_UNICODE);
    $ch = curl_init($url);
    curl_setopt_array($ch, array(
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_HTTPHEADER => array(
            'Content-Type: application/json',
            'Authorization: Bearer ' . $token
        ),
        CURLOPT_POST => 1,
        CURLOPT_POSTFIELDS => $postfields,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_SSL_VERIFYPEER => FALSE,
    ));
    $response = send_request($ch, $debug);
    $ord_id = "$response->id";
    $ord_status = "$response->status";
    $ord_approve = ' '; //$response->{'links'}[1]->{'href'};
    foreach ($response->{'links'} as &$link)
    {
        if($link->{'rel'} == 'approve')
        {
            $ord_approve = $link->{'href'};
        }
    }
    echo "\n\nNew order\nid: " . $ord_id . "\nstatus: " . $ord_status . "\nlink: " . $ord_approve; 
    $file = fopen("paypal_link_" . $pay_id . ".txt", "w+") or die("Не удалось создать файл");
    fwrite($file, $ord_approve);
    fclose($file);
    
    while($ord_status != 'APPROVED')
    {
        sleep(1);
        $url = $home . '/v2/checkout/orders/' . $ord_id;
        $ch = curl_init($url);
        curl_setopt_array($ch, array(
            CURLOPT_RETURNTRANSFER => 1,
            CURLOPT_HTTPHEADER => array(
                'Content-Type: application/json',
                'Authorization: Bearer ' . $token
            ),
            CURLOPT_SSL_VERIFYHOST => FALSE,
            CURLOPT_SSL_VERIFYPEER => FALSE,
        ));
        $response = send_request($ch, $debug);
        $ord_status = $response->{'status'};
        echo "\n\nUpdated status: " . $ord_status;
    }
    
    $url = $home . '/v2/checkout/orders/' . $ord_id . '/capture';
    $ch = curl_init($url);
    curl_setopt_array($ch, array(
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_HTTPHEADER => array(
            'Content-Type: application/json',
            'Authorization: Bearer ' . $token,
            'PayPal-Request-Id: 7b92603e-77ed-4896-8e78-5dea2050476a'
        ),
        CURLOPT_POST => 1,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_SSL_VERIFYPEER => FALSE,
    ));
    $response = send_request($ch, $debug);
    $ord_status = $response->{'status'};
    echo "\n\nResult status: " . $ord_status; 
    
    $file = fopen("paypal_link_" . $pay_id . ".txt", "w+") or die("Не удалось создать файл");
    fwrite($file, "COMPLETE");
    fclose($file);
?>

