<title>Capstone Dashboard</title>
<script src="https://static.robotwebtools.org/roslibjs/current/roslib.min.js"></script>
<script src="https://static.robotwebtools.org/EventEmitter2/current/eventemitter2.min.js"></script>
<script src="https://static.robotwebtools.org/keyboardteleopjs/current/keyboardteleop.min.js"></script>
<script src="//yoannmoinet.github.io/nipplejs/javascripts/nipplejs.js"></script>

<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-giJF6kkoqNQ00vy+HMDP7azOuL0xtbfIcaT9wjKHr8RbDVddVHyTfAAsrekwKmP1" crossorigin="anonymous">
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/js/bootstrap.bundle.min.js" integrity="sha384-ygbV9kiqUc6oa4msXn9868pTtWMgiQaeYH7/t7LECLbyPA2x65Kgf80OJFdroafW" crossorigin="anonymous"></script>


<script>
  var twist;
  var cmdVel;
  var publishImmidiately = true;
  var robot_IP;
  var manager;
  var teleop;
  var ros;

  function moveAction(linear, angular) {
      if (linear !== undefined && angular !== undefined) {
          twist.linear.x = linear;
          twist.angular.z = angular;
      } else {
          twist.linear.x = 0;
          twist.angular.z = 0;
      }
      cmdVel.publish(twist);
  }

  function initVelocityPublisher() {
      // Init message with zero values.
      twist = new ROSLIB.Message({
          linear: {
              x: 0,
              y: 0,
              z: 0
          },
          angular: {
              x: 0,
              y: 0,
              z: 0
          }
      });
      // Init topic object
      cmdVel = new ROSLIB.Topic({
          ros: ros,
          name: '/cmd_vel',
          messageType: 'geometry_msgs/Twist'
      });
      // Register publisher within ROS system
      cmdVel.advertise();
  }


  function initTeleopKeyboard() {
      // Use w, s, a, d keys to drive your robot

      // Check if keyboard controller was aready created
      if (teleop == null) {
          // Initialize the teleop.
          teleop = new KEYBOARDTELEOP.Teleop({
              ros: ros,
              topic: '/cmd_vel'
          });
      }

      // Add event listener for slider moves
      robotSpeedRange = document.getElementById("robot-speed");
      robotSpeedRange.oninput = function () {
          teleop.scale = robotSpeedRange.value / 100
      }
  }


  function createJoystick() {
      // Check if joystick was aready created
      if (manager == null) {
          joystickContainer = document.getElementById('joystick');
          // joystck configuration, if you want to adjust joystick, refer to:
          // https://yoannmoinet.github.io/nipplejs/
          var options = {
              zone: joystickContainer,
              position: { left: 50 + '%', bottom: 105 + 'px' },
              mode: 'static',
              size: 150,
              color: 'grey',
              restJoystick: true
          };
          manager = nipplejs.create(options);
          // event listener for joystick move
          manager.on('move', function (evt, nipple) {
              // nipplejs returns direction is screen coordiantes
              // we need to rotate it, that dragging towards screen top will move robot forward
              var direction = nipple.angle.degree - 90;
              if (direction > 180) {
                  direction = -(450 - nipple.angle.degree);
              }
              // convert angles to radians and scale linear and angular speed
              // adjust if youwant robot to drvie faster or slower
              var lin = Math.cos(direction / 57.29) * nipple.distance * 0.005;
              var ang = Math.sin(direction / 57.29) * nipple.distance * 0.05;
              // nipplejs is triggering events when joystic moves each pixel
              // we need delay between consecutive messege publications to 
              // prevent system from being flooded by messages
              // events triggered earlier than 50ms after last publication will be dropped 
              if (publishImmidiately) {
                  publishImmidiately = false;
                  moveAction(lin, ang);
                  setTimeout(function () {
                      publishImmidiately = true;
                  }, 50);
              }
          });
          // event litener for joystick release, always send stop message
          manager.on('end', function () {
              moveAction(0, 0);
          });
      }
  }

  window.onload = function () {
      // determine robot address automatically
      //robot_IP = location.hostname;
      // set robot address statically
      const urlParams = new URLSearchParams(window.location.search);
      const myParam = urlParams.get('ip');
      if(myParam != null) {
        robot_IP = myParam;
      }
      else {
        robot_IP = "localhost";
      }

      robot_IP = "192.168.68.126";

      // // Init handle for rosbridge_websocket
      ros = new ROSLIB.Ros({
          url: "ws://" + robot_IP + ":9090"
      });

      ros.on('connection', function() {
          console.log('Connection successful!');
          document.getElementById('connected').style.display = 'inline';
          document.getElementById('ip').innerHTML = 'IP: ' + robot_IP;
          document.getElementById('disconnected').style.display = 'none';
      });

      ros.on('close', function() {
          console.log('Connection closed');
          document.getElementById('connected').style.display = 'none';
          document.getElementById('ip').innerHTML = '';
          document.getElementById('disconnected').style.display = 'inline';
      });

      // get handle for video placeholder
      video1 = document.getElementById('video1');
      // Populate video source 
      video1.src = "http://" + robot_IP + ":8080/stream?topic=jetbot_camera";
      createJoystick();
      video.onload = function () {
      // joystick and keyboard controls will be available only when video is correctly loaded
          createJoystick();
          initTeleopKeyboard();
      };

      // get handle for video placeholder
      video2 = document.getElementById('video2');
      // Populate video source 
      video2.src = "http://" + robot_IP + ":8080/stream?topic=jetbot_camera";
  }
</script>

<body style='background-color:#000;'>
  <nav class="navbar navbar-expand-md" style="background-color: #111; padding: 10px 20px;">
    <span class="navbar-brand" style="font-size: 1em; color: #888;">CAPSTONE</span>
      <ul class="navbar-nav mr_auto" style='display: flex; align-items:center;'>
          <div>
              <div>
                <button type="button" class="btn btn-success" id='connected' disabled style='display: none;'>Connected</button>
              </div>
              <div>
                <button type="button" class="btn btn-danger" id='disconnected' data-bs-toggle="tooltip">Disconnected</button>
              </div>
          </div>
          <span id='ip' style='color: grey; margin-left: 5px;'>To change robot IP, add ?ip={ip} to URL</span>
      </ul>
  </nav>

  <div style='display: flex;'>
    <!-- CAMERA -->
    <div style='width: 50%; position: relative;'>
        <span style='position: absolute; top: 10px; left: 10px;' class='badge bg-dark'>CAMERA</span>
        <img src="img/no_signal.png" class="p-1 bg-dark" alt="" id="video1" style='width: 100%;' />
    </div>
    <!-- LIDAR -->
    <div style='width: 50%; position: relative;'>
        <span style='position: absolute; top: 10px; left: 10px;' class='badge bg-dark'>LIDAR</span>
        <img src="img/no_signal.png" class="p-1 bg-dark" alt="" id="video2" style='width: 100%;'/>
    </div>
  </div>

  <!-- JOYSTICK -->
  <div style='display: flex; flex-flow: row nowrap;'>
    <div class="col">
    </div>
    <div class="col">
        <div class="d-flex justify-content-center" style="width: 100px; height: 100px;">
            <div id="joystick"></div>
        </div>
    </div>
    <div class="col">
      <span style='color: #444;'>Wagon Capacity</span>
      <div class="progress" style='height: 10px; width: 200px; background-color: #222; margin-bottom: 20px; box-shadow: 0px 0px 15px 5px rgba(5,218,255,0.2);'>
        <div class="progress-bar bg-info" role="progressbar" style="width: 20%;" aria-valuenow="50" aria-valuemin="0" aria-valuemax="100"></div>
      </div>
      <button type="button" class="btn btn-outline-danger">Emergency Stop</button>
      <button type="button" class="btn btn-outline-warning">Return to Home</button>
    </div>
  </div>
</body>
