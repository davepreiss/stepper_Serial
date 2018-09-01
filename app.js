document.getElementById("forward").onclick = function() {
    forwardstep();
  };
  var pos = 0;

  function forwardstep() {
  // Don't think I need this as he was just trying to prevent tons of mouse clicks from registering
      // var now = new Date();
      // var elapsed = now - lastPost;
      // if (elapsed < 100) {
      //     return;
      // }
      // var mp = snap(mouse());
      // var r = rev(mp);
      // var a1 = -r.a1;
      // var a2 = -r.a2;
        // Drew says make this so that there's an absolute position value instead of a1 and a2 = this is because we are updating an ip address and have no way of sending "just one step" as the ip address is getting updated and the arduino is just looking at it...
      pos += 1;
        $.post("http://127.0.0.1:5000/goto?pos=" + pos);
          // It seems as though Flask is being used python side which defualts to the IP above
    //   lastPost = now;
  }

  // https://api.jquery.com/jquery.post/
  document.getElementById("backward").onclick = function() {
    backwardstep();
  };
  
  function backwardstep() {
    pos -= 1;
    $.post("http://127.0.0.1:5000/goto?pos=" + pos);
      // lastPost = now;
  }
  