package com.example.sase;

import jakarta.persistence.Tuple;
import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import jakarta.websocket.Session;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;

@WebServlet(name = "joinServlet", value = "/join-servlet")
public class JoinServlet extends HttpServlet {

    private Map<SessionPair, Game> games = new HashMap<>();
    private Integer numberOfPlayers = 0;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();

        System.out.println(session.getId());

        if (numberOfPlayers % 2 == 1) {
            for (Map.Entry<SessionPair, Game> entry : games.entrySet()) {
                if (!entry.getKey().isFull()) {
                    entry.getKey().setSecond(session);
                    dispatchToGameServlet(request, response, entry.getKey(), entry.getValue());
                    numberOfPlayers++;
                    return;
                }
            }
        } else {
            SessionPair sessionPair = new SessionPair(session);
            games.put(sessionPair, new Game());
            numberOfPlayers++;
        }

        if (numberOfPlayers % 2 == 1) {
            response.sendRedirect("waiting.jsp");
        }
    }

    private void dispatchToGameServlet(HttpServletRequest request, HttpServletResponse response,
                                       SessionPair sessionPair, Game game) throws ServletException, IOException {
        request.setAttribute("sessionPair", sessionPair);
        request.setAttribute("game", game);

        RequestDispatcher dispatcher = request.getRequestDispatcher("/game-servlet");
        dispatcher.forward(request, response);
    }
}

