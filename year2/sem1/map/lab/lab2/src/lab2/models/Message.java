package lab2.models;

import lab2.constants.Constants;

import java.time.LocalDateTime;

public class Message {
    private String id;
    private String subject;
    private String body;
    private String from;
    private String to;
    private LocalDateTime date;

    public Message(String id, String subject, String body, String from, String to, LocalDateTime date) {
        this.id = id;
        this.subject = subject;
        this.body = body;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getSubject() {
        return subject;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public String getBody() {
        return body;
    }

    public void setBody(String body) {
        this.body = body;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "id=" + this.getId() + "|description=" + this.getSubject() + "|message=" + this.getBody() +
                "|from=" + this.getFrom() + "|to=" + this.getTo() + "|date=" + this.getDate().format(Constants.DATE_TIME_FORMATTER);
    }
}
