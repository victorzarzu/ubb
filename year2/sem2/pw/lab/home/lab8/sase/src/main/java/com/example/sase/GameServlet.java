package com.example.sase;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.util.Map;

@WebServlet(name = "game-servlet", value = "/game-servlet")
public class GameServlet extends HttpServlet {
    private SessionPair sessionPair;
    private Game game;

    public GameServlet() {
    }

    public GameServlet(SessionPair sessionPair, Game game) {
        this.sessionPair = sessionPair;
        this.game = game;
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();

        //response.setIntHeader("Refresh", 1);

        // Your game logic goes here using the sessionPair and game objects

        //response.sendRedirect("index.jsp");
    }
}
