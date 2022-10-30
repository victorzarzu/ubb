public class ColorDecorator extends RoomDecorator {
      
      public ColorDecorator (Room specialRoom) {  
        super(specialRoom);  
      }  
      
      public String showRoom() {  
        return specialRoom.showRoom() + addColors();  
      }  
      
      private String addColors() {  
        return " + Blue Color";  
      }  
    }  


