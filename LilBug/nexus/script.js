// var ip = "192.168.2.63";
var ip = "192.168.1.1";

nx.onload = function() {
    console.log("start");
    nx.sendsTo("js");
//    s1.on("value", nx.throttle(function(data) { controlChange(1, Math.floor(data*127)); }, 500) );
    s1.on("value", nx.widgets.s1.throttle(function(data) { controlChange(1, Math.floor(data*127)); }, 500) );
//  s1.on("value", function(data) { controlChange(1, Math.floor(data*127)); });
    s2.on("value", function(data) { controlChange(2, Math.floor(data*127)); });
    s3.on("value", function(data) { controlChange(3, Math.floor(data*127)); });
    s4.on("value", function(data) { controlChange(4, Math.floor(data*127)); });
    p1.on("x", function(data) { controlChange(10, Math.floor(data*127)); });
    p1.on("y", function(data) { controlChange(20, Math.floor(data*127)); });
    k1.on("midi", function(data) { var data = data.split(" ");
				   note(data[0], data[1]); });
    nx.setThrottlePeriod(500);
}

function controlChange(cc, value){
    console.log("cc "+cc+": "+value);
    var img = document.createElement('img');
    img.src = "http://"+ip+"/control?cc="+cc+"&value="+value;
}

function note(note, state){
    console.log("note "+note+": "+(state == 1?"on":"off"));
    var img = document.createElement('img');
    var velocity = 80;
    if(state == 1)
	img.src = "http://"+ip+"/note?pitch="+note+"&velocity="+velocity;
    else
	img.src = "http://"+ip+"/note?pitch="+note;
}
