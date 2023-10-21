package com.example.sase;

import jakarta.servlet.http.HttpSession;
import jakarta.websocket.Session;

import java.util.Objects;

public class SessionPair {
    private HttpSession first;
    private HttpSession second;

    public SessionPair(HttpSession first, HttpSession second) {
        this.first = first;
        this.second = second;
    }

    public SessionPair(HttpSession first) {
        this.first = first;
        this.second = null;
    }

    public HttpSession getFirst() {
        return first;
    }

    public HttpSession getSecond() {
        return second;
    }

    public boolean isFull() {
        return second != null;
    }

    public void setSecond(HttpSession second) {
        this.second = second;
    }

    public boolean isIn(HttpSession session) {
        return second != null && (first.equals(session) || second.equals(session));
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        SessionPair that = (SessionPair) o;
        return Objects.equals(first, that.first) && Objects.equals(second, that.second);
    }

    @Override
    public int hashCode() {
        return Objects.hash(first, second);
    }
}
