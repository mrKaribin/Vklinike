package com.vklinike;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;
import java.util.Calendar;
import java.util.concurrent.ExecutionException;

public class DataPacker
{
    private byte[] field_array;

    private ByteArrayOutputStream object_stream;
    private ByteBuffer object_buffer;

    public DataPacker()
    {
        object_stream = new ByteArrayOutputStream();
    }

    public void add(String value)
    {
        byte[] array =  value.getBytes();
        try {
            object_stream.write(array);
        }
        catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
