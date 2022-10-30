abstract class RoomDecorator implements Room{
      
      protected Room specialRoom;  
      
      public RoomDecorator (Room specialRoom) {  
        this.specialRoom= specialRoom;  
      }  
      
     public String showRoom() {  
        return specialRoom.showRoom();  
      }  
    }  


