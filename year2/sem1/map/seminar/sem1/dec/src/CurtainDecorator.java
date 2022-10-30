public class CurtainDecorator extends RoomDecorator {
      
      public CurtainDecorator (Room specialRoom) {  
        super(specialRoom);  
      }  
      
      public String showRoom() {  
        return specialRoom.showRoom() + addCurtains();  
      }  
      
      private String addCurtains() {  
        return " + Red Curtains";  
      }  
    }  


