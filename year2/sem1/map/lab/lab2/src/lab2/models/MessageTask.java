package lab2.models;

import java.time.LocalDateTime;

public class MessageTask extends Task {
    Message message;

    public MessageTask(String taskID, String descriere, String mesaj, String from, String to, LocalDateTime date) {
        super(taskID, descriere);
        message = new Message(taskID, descriere, mesaj, from, to, date);
    }

    @Override
    public String toString() {
        return message.toString();
    }

    @Override
    public void execute() {
        System.out.println(this.toString());
    }
}
