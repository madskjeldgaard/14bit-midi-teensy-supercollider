/*********************************/
/* Using the FourteenbitCC class */
/*********************************/
// Get it here: https://gist.github.com/carltesta/bb5065a7b92bab7673237e9cc1c9a612
(
MIDIIn.connectAll;

~x = FourteenBitCC.new("x", 16, 48);
~x.func = {|val| 
	var bits = 13,
	maxval = (2**bits-1);

	Ndef(\s).set(\carfreq, val.linexp(0, 2**13, 50.0,15000.0));
	("x: "++val).postln
};

~y = FourteenBitCC.new("y", 17, 49, 0);
~y.func = {|val| 
	var bits = 13,
		maxval = (2**bits-1);

	Ndef(\s).set(\freq, val.linexp(0, maxval, 50.0,5000.0));
	("y: "++val).postln;
};

Ndef(\s, {|freq=444, carfreq=919| SinOsc.ar(freq * SinOsc.ar(carfreq))*0.5!2}).mold(2).play;
)

MIDIFunc.trace(true)

/*********************************/
/* Using Modality 				 */
/*********************************/

MKtl.find(\midi);

(
~descInput = (
	idInfo: "Teensy MIDI",
	deviceName: "Teensy MIDI",
    protocol: \midi,
    elementsDesc: (
        elements: (16..20).collect{|lowerMidiCC|
			(
                key: "kn%".format(lowerMidiCC).asSymbol,
                type: 'knob',
                spec: [0,16383,\lin,1,0],
                midiMsgType: \cc14,
                midiChan: 0,
                midiNum: lowerMidiCC,
                ioType: \in
            )
		}
    )
);

);

m = MKtl( \testMIDI, ~descInput );
m.trace(true)

m.elAt

m.rebuild(~descInput);

2**13


0.15 / 0.05
