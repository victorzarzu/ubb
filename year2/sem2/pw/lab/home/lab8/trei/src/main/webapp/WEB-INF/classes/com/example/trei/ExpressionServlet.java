package com.example.trei;

import jakarta.servlet.http.HttpServlet;

public class ExpressionServlet extends HttpServlet {

    private static final String url = "jdbc:postgresql://localhost:5432/pwlab8";
    private static final String db_username = "postgres";
    private static final String db_password = "admin";
    private static final String dbDriver = "org.postgresql.Driver";
}
