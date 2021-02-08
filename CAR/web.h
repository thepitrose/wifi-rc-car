R"=====(
<!DOCTYPE HTML>
<html>
    <head>
    </head>
<body>

  <p>Press any button on the joystick , for  mapping </p>
  <form action="http://192.168.14.203/submit" method="POST">

<div><img id="Arducam" src="http://192.168.14.203/stream"></div>
</form>

</body>

  <script>

window.addEventListener("gamepadconnected", function(e) {
  var gp = navigator.getGamepads()[e.gamepad.index];
  //alert("A " + gp.id + " was successfully detected!")

  setInterval(function(){

var xhr = new XMLHttpRequest();


      let axeLR = (navigator.getGamepads()[0].axes[0]).toFixed(3);
    
     var url = "/stopside";
     xhr.open("GET", url, true);
     xhr.send();

    

    if (navigator.getGamepads()[0].buttons[7].pressed==true)
    {
       // buttons RT
    }

     if (navigator.getGamepads()[0].buttons[0].pressed==true)
    {
      // buttons A
     var url = "/forward";
      xhr.open("GET", url, true);
       xhr.send();
    }

     else if (navigator.getGamepads()[0].buttons[2].pressed==true)
    {
       //buttons X
       var url = "/dback";
       xhr.open("GET", url, true);
       xhr.send();
    }

     else if (navigator.getGamepads()[0].buttons[7].pressed==false )
       {
         var url = "/stopme";
         xhr.open("GET", url, true);
         xhr.send();
       }
    
     if  (navigator.getGamepads()[0].axes[0]==true)
      {
       var url = "/dright";
       xhr.open("GET", url, true);
       xhr.send();   
      }

     if (axeLR<0)
      { 
        var url = "/dleft";
        xhr.open("GET", url, true);
        xhr.send(); 
       }
  

  }, 100)
});
  </script>

  
</body>

</html>
)=====";
