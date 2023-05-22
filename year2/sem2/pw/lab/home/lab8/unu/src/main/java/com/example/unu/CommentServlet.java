package com.example.unu;

import java.io.*;

import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;

@WebServlet("/comment-servlet")
public class CommentServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String comment = request.getParameter("comment");

        System.out.println(name);
        System.out.println(comment);

        // Process the posted comment data, e.g., save it to a database or store it in a file.

        // You can send a response back to the client if needed.
        response.sendRedirect("index.html");
    }
}