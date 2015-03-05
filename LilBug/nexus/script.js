// var ip = "192.168.2.63";
var ip = "192.168.1.1";
var throttlePeriod;

function throttle(fn, scope) {
    if(!throttlePeriod)
	return fn;
    var last, deferTimer;    
    return function () {
    var context = scope || this;
    var now = +new Date,
        args = arguments;
    if (last && now < last + throttlePeriod) {
      // hold on to it
      clearTimeout(deferTimer);
      deferTimer = setTimeout(function () {
        last = now;
        fn.apply(context, args);
      }, throttlePeriod);
    } else {
      last = now;
      fn.apply(context, args);
    }
  };
}

nx.onload = function() {
    console.log("start");
    nx.sendsTo("js");
//    s1.on("value", function(data) { controlChange(1, Math.floor(data*127)); });
//    s1.on("value", nx.throttle(function(data) { controlChange(1, Math.floor(data*127)); }, 500) );
    s1.on("value", throttle(function(data) { controlChange(1, Math.floor(data*127)); }));
    s2.on("value", throttle(function(data) { controlChange(2, Math.floor(data*127)); }));
    s3.on("value", throttle(function(data) { controlChange(3, Math.floor(data*127)); }));
    s4.on("value", throttle(function(data) { controlChange(4, Math.floor(data*127)); }));
    p1.on("x", throttle(function(data) { controlChange(10, Math.floor(data*127)); }));
    p1.on("y", throttle(function(data) { controlChange(20, Math.floor(data*127)); }));
    k1.on("midi", throttle(function(data) { var data = data.split(" ");
					    note(data[0], data[1]); }));
    nx.setThrottlePeriod(50);
    $('#wsServer').val("ws://"+ip+":8080/midi");
    setupWebsocket();
}

var ws;
function setupWebsocket(){
    $('#connectForm').on('submit', function() {
        if("WebSocket" in window) {
            ws = new WebSocket($('#wsServer').val());
	    ws.binaryType = 'arraybuffer';
            ws.onopen = function() {
                $('#log').append('<li><span class="badge badge-success">websocket opened</span></li>');
                $('#wsServer').attr('disabled', 'disabled');
                $('#connect').attr('disabled', 'disabled');
                $('#disconnect').removeAttr('disabled');
                $('#message').removeAttr('disabled').focus();
                $('#send').removeAttr('disabled');
            };
            ws.onerror = function() {
                $('#log').append('<li><span class="badge badge-important">websocket error</span></li>');
		ws = undefined;
            };
            ws.onmessage = function(event) {
		if(msg.data instanceof ArrayBuffer){
		    sendMidiData(event.data);
		    var str = [];
		    var view = new DataView(event.data);
		    for(i=0; i<event.data.byteLength; ++i){
			str.push(view.getUint8(i).toString(16));
		    }
                    $('#log').append('<li>received ' + event.data.byteLength + ' bytes: <span class="badge">0x' + str.join(" 0x") + '</span></li>');
		}else{
                    $('#log').append('<li>received text: <span class="badge">' + event.data + '</span></li>');
		}
            };
            ws.onclose = function() {
                $('#log').append('<li><span class="badge badge-important">websocket closed</span></li>');
                $('#wsServer').removeAttr('disabled');
                $('#connect').removeAttr('disabled');
                $('#disconnect').attr('disabled', 'disabled');
                $('#message').attr('disabled', 'disabled');
                $('#send').attr('disabled', 'disabled');
		ws = undefined;
            };

        } else {
            $('#log').append('<li><span class="badge badge-important">WebSocket NOT supported in this browser</span></li>');
        }
        return false;
    });
    $('#sendForm').on('submit', function() {
	//                var message = $('#message').val();
	//                ws.send(message);
	var message = new Int8Array(3);
	message.set([0x80, 60, 80]);
	ws.send(message);
        $('#log').append('<li>sent: <span class="badge">' + message + '</span></li>');
        return false;
    });
    $('#disconnect').on('click', function() {
        ws.close();
        return false;
    });
    $('#clear').on('click', function() {
	$('#log').empty();
	return false;
    });
}

function controlChange(cc, value){
    console.log("cc "+cc+": "+value);
    // var img = document.createElement('img');
    // img.src = "http://"+ip+"/control?cc="+cc+"&value="+value;
    if(ws){
	var message = new Int8Array(3);
	message.set([0xB0, cc, value]);
	ws.send(message);
    }
}

function note(note, state){
    console.log("note "+note+": "+(state == 1?"on":"off"));
    // var img = document.createElement('img');
    // var velocity = 80;
    // if(state == 1)
    // 	img.src = "http://"+ip+"/note?pitch="+note+"&velocity="+velocity;
    // else
    // 	img.src = "http://"+ip+"/note?pitch="+note;
    if(ws){
	var message = new Int8Array(3);
	var velocity = state == 1 ? 80 : 0;
	message.set([0x90, note, velocity]);
	ws.send(message);
    }
}
