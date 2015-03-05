$(document).ready(function() {
    setupWebsocket();
    setupMidi();
});

var ws;
function setupWebsocket(){
    $('#connectForm').on('submit', function() {
        if ("WebSocket" in window) {
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
                $('#log').append('<li>received: <span class="badge">' + event.data + '</span></li>');
		sendMidiData(event.data);
		var str = [];
		var view = new DataView(event.data);
		for(i=0; i<event.data.byteLength; ++i){
		    str.push(view.getUint8(i).toString(16));
		}
                $('#log').append('<li>decoded ' + event.data.byteLength + ' bytes: <span class="badge">0x' + str.join(" 0x") + '</span></li>');
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
}

function MIDIMessageEventHandler(event) {
    console.log("MIDI 0x"+event.data[0].toString(16)+" "+event.data.length+" bytes");
    if(ws){
	var message = new Int8Array(event.data, 0, event.data.length);
	ws.send(message);
	$('#log').append('<li>sent: ' + message.bytesLength + ' bytes</li>');
    }
}

var midiAccess = null;  // global MIDIAccess object
var midiOutputs = [];
var midiOutput = null;

function onMIDIInit(midi, options) {
    midiAccess = midi;
    var inputs = midiAccess.inputs();
    if (inputs.length === 0)
	console.log("No MIDI input devices present.")
    else { // Hook the message handler for all MIDI inputs
	for (var i=0;i<inputs.length;i++){
	    console.log("adding MIDI input "+inputs[i].name+" ("+inputs[i].manufacturer+") "+inputs[i].id);
	    inputs[i].onmidimessage = MIDIMessageEventHandler;
	}
    }
    var outputs = midiAccess.outputs();
    if (outputs.length === 0)
	console.log("No MIDI output devices present.")
    else {
	for (var i=0;i<outputs.length;i++){
	    console.log("adding MIDI output "+outputs[i].name+" ("+outputs[i].manufacturer+") "+outputs[i].id);
            midiOutputs.push(outputs[i]);
	    registerMidiOutput(i, outputs[i].name);
	}
        midiOutput = outputs[outputs.length - 1];
    }
}

function selectMidiOutput(index) {
    midiOutput = midiOutputs[index];
    if(midiOutput)
      console.log("selecting MIDI output "+index+": "+midiOutput.name+" ("+midiOutput.manufacturer+")");
}

function sendCc(cc, value) {
    // console.log("sending CC "+cc+"/"+value);
    if(midiOutput)
      midiOutput.send([0xB0, cc, value], 0);
}

function sendMidiData(data) {
    if(midiOutput)
      midiOutput.send(data, 0);
}

function onMIDIReject(err) {
    alert("The MIDI system failed to start.");
}

function setupMidi(){
    // patch up prefixes
    window.AudioContext = window.AudioContext||window.webkitAudioContext;
    context = new AudioContext();
    var options = { sysex: false }; // change to true for sysex messaging
    if (navigator.requestMIDIAccess)
	navigator.requestMIDIAccess(options).then( onMIDIInit, onMIDIReject );
    else
	alert("No MIDI support present in your browser.")
}
