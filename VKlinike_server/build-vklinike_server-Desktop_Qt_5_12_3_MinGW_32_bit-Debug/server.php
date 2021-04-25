<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class Client
{   
    function sendFile(string $header, string $dir)
    {
        if(($file = fopen($dir, "r")) !== FALSE)
        {
            $content_size = filesize($dir);
            $content = fread($file, $content_size);
            fclose($file);

            $header_size = strlen($header);
            $block_size = $header_size + $content_size + 8;

            echo "\nData prepared:\n";
            echo "Block size: $block_size bytes\n";
            echo "Header: $header_size bytes ($header)\n";
            echo "Content: $content_size bytes\n";

            //$key = array(0x012, 0x023, 0x034, 0x045);
            $key = array(0x045, 0x034, 0x023, 0x012);
            socket_write($this->socket, pack("L", 0x012), 1);
            socket_write($this->socket, pack("L", 0x023), 1);
            socket_write($this->socket, pack("L", 0x034), 1);
            socket_write($this->socket, pack("L", 0x045), 1);
            socket_write($this->socket, pack("L", $block_size), 4);
            //socket_send($socket, 0x002, 4);
            socket_write($this->socket, pack("L", $header_size), 4);
            socket_write($this->socket, $header, $header_size);
            socket_write($this->socket, pack("L", $content_size), 4);
            socket_write($this->socket, $content, $content_size);
            echo "Data send\n";
        }
        else
            echo "Can't open file: $dir";
    }
    
    public $socket;
    public $ip;
    public $port;
}


set_time_limit(0);
ob_implicit_flush();

$service_adress = gethostbyname("192.168.1.10");
$service_port = 10200;
$adress = gethostbyname("192.168.1.10"); //delphino.ddnsking.com
$port = 10322;

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
$connector = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
$controller = null;
$clients = array();

if(socket_bind($connector, $service_adress, $service_port) === FALSE){
    echo "Can't bind connector: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit();
}

if(socket_listen($connector) === FALSE){
    echo "Can't listen connector: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit();
}

if(socket_set_nonblock($connector) === FALSE){
    echo "Connector setting error: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit();
}

echo "Connector initialized\n";
echo "Adress: $service_adress\n";
echo "Port: $service_port\n";

if(socket_bind($socket, $adress, $port) === FALSE){
    echo "Can't bind socket: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit();
}

if(socket_listen($socket) === FALSE){
    echo "Can't listen socket: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit();
}

if(socket_set_nonblock($socket) === FALSE){
    echo "Socket setting error: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit();
}

echo "\nServer initialized\n";
echo "Adress: $adress\n";
echo "Port: $port\n";

while(TRUE)
{
    if(($client_sock = socket_accept($socket)) !== FALSE)
    {
        $client = new Client();
        $client->socket = $client_sock;
        socket_getpeername($client->socket, $client->ip, $client->port);
        $clients[] = $client;
        echo "\nClient connected:\n";
        echo "adress: $client->ip\n";
        echo "port: $client->port\n";
        
        //$client->sendFile('file_58', 'Files\Attachment\file_58.jpg');
    }
    
    if(($sock = socket_accept($connector)) !== FALSE)
    {
        $controller = $sock;
        echo "\nController connected\n";
    }
    
    if($controller != null && 
            ((int)$size = socket_read($controller, 4, PHP_BINARY_READ)) != '')
    {
        $data = socket_read($controller, $size, PHP_BINARY_READ);
        //echo "\nController received ($size): $data\n";
        if($data != "")
        {
            $json = json_decode($data);
            if($json->command == "SendFile")
            {
                echo "\nCommand SendFile\n";
                $ip = $json->ip;
                $header = $json->header;
                $path = $json->path;
                foreach ($clients as $element){
                    if($element->ip == $ip){
                        $client = $element;
                        echo "\nClient found\n";
                        echo "ip: $ip\n";
                        echo "header: $header\n";
                        echo "path: $path\n";
                        $client->sendFile($header, $path);
                    }
                }
            }
        }
    }
}

echo "Can't accepting: " . socket_strerror(socket_last_error($socket)) . "\n";

