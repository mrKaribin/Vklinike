package com.vklinike.ui.socket;

import android.database.CharArrayBuffer;
import android.os.AsyncTask;
import android.os.Environment;
import android.util.ArrayMap;
import android.util.Log;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.vklinike.GlobalData;
import com.vklinike.data.Request;

import java.io.BufferedWriter;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class ClientSocket extends AsyncTask <Void, ClientSocket.ReceivePackage, ClientSocket.OnConnectionListener>
{

    private String field_host = "";
    private int field_port = 0;
    private boolean field_run = false;
    private boolean field_crash = false;
    private int field_nextBlock_size = 0;
    private int field_nextBlock_index = 0;
    private byte[] field_nextBlock = null;
    private int field_nextBlock_type = 0;
    private byte[] field_key;

    private List<Request> array_packages_input;
    private List<byte[]> array_packages_output;
    private Map<String, byte[]> array_enclosures;
    private Map<String, OnMessageReceived> array_expected_requests;
    private Map<String, OnEnclosureReceived> array_expected_enclosures;
    private Map<String, List<OnMessageReceived>> array_fixed;

    private Socket object_socket;
    private Socket object_socket2;
    private PrintWriter object_buffer_out;

    public class ReceivePackage
    {
        public ReceivePackage(OnMessageReceived _function, JsonObject _object) {
            interface_package = _function;
            object = _object;
            interface_enclosure = null;
        }

        public ReceivePackage(OnEnclosureReceived _interface, byte[] _enclosure){
            interface_enclosure = _interface;
            enclosure = _enclosure;
            interface_package = null;
        }

        public OnMessageReceived interface_package;
        public JsonObject object;
        public OnEnclosureReceived interface_enclosure;
        public byte[] enclosure;
    }

    private OnConnectionListener interface_connection = null;

    public ClientSocket(String _host, int _port)
    {
        field_host = _host;
        field_port = _port;
        field_key = new byte[4];
        field_key[0] = 0x012;
        field_key[1] = 0x023;
        field_key[2] = 0x034;
        field_key[3] = 0x045;
                array_packages_input = new ArrayList<Request>();
        array_packages_output = new ArrayList<byte[]>();
        array_enclosures = new ArrayMap<String, byte[]>();
        array_expected_requests = new ArrayMap<String, OnMessageReceived>();
        array_expected_enclosures = new ArrayMap<String, OnEnclosureReceived>();
        array_fixed = new ArrayMap<String, List<OnMessageReceived>>();
    }

    private void clearNextBlock(){
        field_nextBlock_size = 0;
        field_nextBlock_type = 0;
        field_nextBlock = new byte[0];
    }

    private byte[] reverse(byte[] array)
    {
        int max = array.length - 1;
        for(int i = 0; i < array.length / 2; i++){
            byte buf = array[i];
            array[i] = array[max - i];
            array[max - i] = buf;
        }
        return array;
    }

    @Override
    protected OnConnectionListener doInBackground(Void... voids) {
        try{
            InetAddress address = InetAddress.getByName(field_host);
            object_socket = new Socket(address, field_port);
            if (interface_connection != null)
                interface_connection.onConnected();
            object_buffer_out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(object_socket.getOutputStream())), true);
            field_run = true;

            while (field_run) {
                if (object_buffer_out.checkError() || !object_socket.isConnected() ) { //|| !object_socket2.isConnected()
                    field_run = false;
                    if(interface_connection != null)
                        return interface_connection;
                }

                if(array_packages_output.size() != 0)
                {
                    try{
                        for(int i = 0; i < array_packages_output.size(); i++)
                            object_socket.getOutputStream().write(array_packages_output.get(i));
                    } catch (Exception e){
                        field_nextBlock_index = 0;
                    }
                    array_packages_output.clear();
                }

                if(field_nextBlock_size == 0) {
                    if(object_socket.getInputStream().available() >= 9) {
                        byte[] prefix = new byte[4];
                        do{
                            prefix[0] = (byte) object_socket.getInputStream().read();
                            if(prefix[0] == field_key[0]){
                                prefix[1] = (byte) object_socket.getInputStream().read();
                                prefix[2] = (byte) object_socket.getInputStream().read();
                                prefix[3] = (byte) object_socket.getInputStream().read();

                                if(prefix[1] == field_key[1] && prefix[2] == field_key[2] && prefix[3] == field_key[3]){
                                    byte[] value_data = new byte[4];
                                    int readed = object_socket.getInputStream().read(value_data, 0, 4);
                                    field_nextBlock_type = object_socket.getInputStream().read();
                                    field_nextBlock_size = getInt(value_data);
                                    field_nextBlock = new byte[0];
                                    break;
                                }
                            }
                        } while(object_socket.getInputStream().available() >= 9);
                    }
                    if (field_nextBlock_size <= 0)
                        continue;
                }

                int count = 0;
                boolean dataIsAvailable = true;
                while(field_nextBlock.length < field_nextBlock_size){
                    int available = object_socket.getInputStream().available();
                    if(available != 0) {
                        count = 0;
                        int size = available;
                        if (available + field_nextBlock.length > field_nextBlock_size)
                            size = field_nextBlock_size - field_nextBlock.length;
                        byte[] newBlock = new byte[size];
                        object_socket.getInputStream().read(newBlock, 0, size);

                        byte[] newNextBlock = new byte[field_nextBlock.length + size];
                        int index = 0;
                        for (int i = 0; i < field_nextBlock.length; i++) {
                            newNextBlock[index] = field_nextBlock[i];
                            index++;
                        }
                        for (int i = 0; i < newBlock.length; i++) {
                            newNextBlock[index] = newBlock[i];
                            index++;
                        }
                        field_nextBlock = newNextBlock;
                    }
                    else {
                        Thread.sleep(100);
                        count++;
                        if(count == 100){
                            dataIsAvailable = false;
                            break;
                        }
                    }
                }

                if(!dataIsAvailable){
                    clearNextBlock();
                    continue;
                }

                ByteArrayInputStream stream = new ByteArrayInputStream(field_nextBlock);
                if(field_nextBlock_type == 0x001) {
                    String json = new String(field_nextBlock);
                    Request message = new Request(new JsonParser().parse(json).getAsJsonObject());

                    boolean readed = false;
                    OnMessageReceived listener = array_expected_requests.get(message.header);
                    if (listener != null) {
                        ReceivePackage pack = new ReceivePackage(listener, message.body);
                        array_expected_requests.remove(message.header);
                        publishProgress(pack);
                        readed = true;
                    }
                    List<OnMessageReceived> list = array_fixed.get(message.header);
                    if (list != null) {
                        for (int i = 0; i < list.size(); i++) {
                            ReceivePackage pack = new ReceivePackage(list.get(i), message.body);
                            publishProgress(pack);
                            readed = true;
                        }
                    }
                    if(!readed) {
                        array_packages_input.add(message);
                    }
                }
                else if(field_nextBlock_type == 0x002){
                    String header;
                    byte[] enclosure;

                    int size = 0;
                    byte[] buffer_size = new byte[4];
                    int readed = stream.read(buffer_size, 0, 4);
                    size = getInt(buffer_size);

                    byte[] buffer_header = new byte[size];
                    readed = stream.read(buffer_header, 0, size);
                    CharArrayBuffer buffer = new CharArrayBuffer(10);
                    header = new String(buffer_header);

                    buffer_size = new byte[4];
                    readed = stream.read(buffer_size, 0, 4);
                    size = getInt(buffer_size);

                    enclosure = new byte[size];
                    readed = stream.read(enclosure, 0, size);

                    OnEnclosureReceived receiver = array_expected_enclosures.get(header);
                    if(receiver != null) {
                        ReceivePackage pack = new ReceivePackage(receiver, enclosure);
                        publishProgress(pack);
                    }
                    else
                        array_enclosures.put(header, enclosure);
                }

                clearNextBlock();
            }
        }
        catch (Exception e) {
            field_nextBlock_index = 0;
        }
        finally {
            return interface_connection;
        }
    }

    @Override
    protected void onProgressUpdate(ReceivePackage... values) {
        if(values[0].interface_package != null)
            values[0].interface_package.received(values[0].object);
        if(values[0].interface_enclosure != null)
            values[0].interface_enclosure.received(values[0].enclosure);
    }

    @Override
    protected void onPostExecute(OnConnectionListener onConnectionListener) {
        disconnected();
        if(onConnectionListener != null) {
            try {
                onConnectionListener.onDisconnected();

            } catch (Exception e){
                field_crash = true;
            }
        }
    }

    public void disconnected()
    {
        if (object_socket != null && object_socket.isConnected()) {
            try {
                object_socket.close();
            } catch (Exception e){
                field_crash = true;
            }
        }
    }

    public void stopClient() {
        Request pack = new Request("Disconnect");
        pack.body.addProperty("status", "default");
        sendMessage(pack);

        field_run = false;

        if (object_buffer_out != null) {
            object_buffer_out.flush();
            object_buffer_out.close();
        }

        array_packages_input.clear();
        //object_buffer_in = null;
        object_buffer_out = null;
        field_nextBlock = null;
        field_nextBlock_size = 0;
        field_nextBlock_index = 0;
    }

    public void setOnConnection(OnConnectionListener listener){
        GlobalData.interface_connection = listener;
        interface_connection = listener;
    }

    public byte[] getEnclosure(String header){
        byte[] result = array_enclosures.get(header);
        if(result != null) {
            array_enclosures.remove(header);
            return result;
        }
        else
            return new byte[1];
    }

    public void sendMessage(Request pack)
    {
        sendMessage(pack.header, pack.body);
    }

    public void sendMessage(String header, JsonObject body){
        if (object_buffer_out != null && !object_buffer_out.checkError()) {
            JsonObject request = new JsonObject();
            request.addProperty("header", header);
            request.add("body", body);
            byte[] request_data = request.toString().getBytes();
            byte[] length = ByteBuffer.allocate(4).putInt(request_data.length).array();
            byte type = 0x001;
            ByteArrayOutputStream buffer = new ByteArrayOutputStream();

            buffer.write(field_key, 0, 4);
            buffer.write(length, 0, 4);
            buffer.write(type);
            buffer.write(request_data, 0, request_data.length);
            array_packages_output.add(buffer.toByteArray());
        }
    }

    public void sendEnclosure(String header, byte[] object){
        if (object_buffer_out != null && !object_buffer_out.checkError()) {
            int length = 0;
            length += object.length + header.length() + 8;
            byte[] _length = ByteBuffer.allocate(4).putInt(length).array();
            byte type = 0x002;
            ByteArrayOutputStream buffer = new ByteArrayOutputStream();

            buffer.write(field_key, 0, 4);
            buffer.write(_length, 0 , 4);
            buffer.write(type);
            buffer.write(ByteBuffer.allocate(4).putInt(header.length()).array(), 0, 4);
            buffer.write(header.getBytes(), 0, header.length());
            buffer.write(ByteBuffer.allocate(4).putInt(object.length).array(), 0, 4);
            buffer.write(object, 0, object.length);

            array_packages_output.add(buffer.toByteArray());
        }
    }

    public void addExpectedRequest(String header, OnMessageReceived function)
    {
        for(Request request : array_packages_input) {
            if(request.header.equals(header)){
                function.received(request.body);
                array_packages_input.remove(request);
                return;
            }
        }
        array_expected_requests.remove(header);
        array_expected_requests.put(header, function);
    }

    public void addFixedRequest(String header, OnMessageReceived function)
    {
        for(Request request : array_packages_input) {
            if(request.header.equals(header)){
                function.received(request.body);
                array_packages_input.remove(request);
            }
        }

        List<OnMessageReceived> list = array_fixed.get(header);
        if(list != null){
            list.add(function);
            array_fixed.put(header, list);
        }
        else {
            list = new ArrayList<OnMessageReceived>();
            list.add(function);
            array_fixed.put(header, list);
        }
    }

    public void addExpectedEnclosure(String header, OnEnclosureReceived function)
    {
        byte[] enclosure = array_enclosures.get(header);
        if(enclosure != null){
            array_enclosures.remove(header);
            function.received(enclosure);
        }
        else
            array_expected_enclosures.put(header, function);
    }

    private int getInt(byte[] value) {
        int res = 0;
        for (int i = 0; i < 4; ++i) {
            res = (res << 8) | value[i] & 0xFF;
        }
        return res;
    }

    public interface OnAction{
        void action();
    }

    public interface OnMessageReceived{
        void received(JsonObject body);
    }

    public interface OnEnclosureReceived{
        void received(byte[] body);
    }

    public interface OnConnectionListener{
        void onConnected();
        void onDisconnected();
    }
}
