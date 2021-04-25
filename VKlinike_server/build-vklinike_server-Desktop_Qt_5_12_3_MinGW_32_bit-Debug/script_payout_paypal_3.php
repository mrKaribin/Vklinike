<?php

    $debug = FALSE;
    $sandbox = FALSE;
    
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
        $token = $argv[1];
    }
    
    if($argc > 2)
    {
        $ord_id = $argv[2];
    }
    
    if($argc > 3)
    {
        $pay_id = $argv[3];
    }
    
    if($sandbox === TRUE)
    {
        $home = 'https://api.sandbox.paypal.com'; 
    }
    else
    {
        $home = 'https://api.paypal.com';    
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
    fwrite($file, $ord_status);
    fclose($file);
?>

