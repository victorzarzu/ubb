package com.example.trei;

import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpServletResponseWrapper;

import java.io.CharArrayWriter;
import java.io.PrintWriter;

public class CharResponseWrapper extends HttpServletResponseWrapper {
    private CharArrayWriter writer;
    private PrintWriter printWriter;
    private String contentType = "text/html";

    public CharResponseWrapper(HttpServletResponse response) {
        super(response);
        writer = new CharArrayWriter();
    }

    @Override
    public PrintWriter getWriter() {
        if (printWriter == null) {
            printWriter = new PrintWriter(writer);
        }
        return printWriter;
    }

    public String getContentType() {
        return contentType;
    }

    public String toString() {
        return writer.toString();
    }

}
