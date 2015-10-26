<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="no" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="no" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="no" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="no" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="no" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="no" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="no" active="yes"/>
<layer number="108" name="fp8" color="7" fill="1" visible="yes" active="yes"/>
<layer number="109" name="fp9" color="7" fill="1" visible="yes" active="yes"/>
<layer number="110" name="fp0" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="LPC17xx" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="Max.sfx.Comments" color="9" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="no" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="no" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="no" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="no" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="yes" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="no" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="no" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="6" fill="1" visible="no" active="no"/>
<layer number="154" name="FabDoc2" color="2" fill="1" visible="no" active="no"/>
<layer number="155" name="FabDoc3" color="7" fill="15" visible="no" active="no"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="no" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="no" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="no" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="no" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="no" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="no" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="no" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="no" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="no" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="no" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="smartplug">
<packages>
<package name="SOIC16N">
<description>&lt;b&gt;SMALL OUTLINE INTEGRATED CIRCUIT&lt;/b&gt;</description>
<wire x1="4.94" y1="-1.9" x2="-4.94" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-4.94" y1="-1.9" x2="-4.94" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-4.94" y1="-1.4" x2="-4.94" y2="1.9" width="0.2032" layer="51"/>
<wire x1="-4.94" y1="1.9" x2="4.94" y2="1.9" width="0.2032" layer="51"/>
<wire x1="4.94" y1="-1.4" x2="-4.94" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.94" y1="1.9" x2="4.94" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.94" y1="-1.4" x2="4.94" y2="-1.9" width="0.2032" layer="51"/>
<smd name="2" x="-3.175" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="13" x="-0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-4.445" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="-0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="14" x="-1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="12" x="0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="11" x="1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="9" x="4.445" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="3.175" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="10" x="3.175" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="4.445" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="15" x="-3.175" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="16" x="-4.445" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-5.207" y="-1.905" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-4.69" y1="-3.1" x2="-4.2" y2="-2" layer="51"/>
<rectangle x1="-3.42" y1="-3.1" x2="-2.93" y2="-2" layer="51"/>
<rectangle x1="-2.15" y1="-3.1" x2="-1.66" y2="-2" layer="51"/>
<rectangle x1="-0.88" y1="-3.1" x2="-0.39" y2="-2" layer="51"/>
<rectangle x1="1.66" y1="2" x2="2.15" y2="3.1" layer="51"/>
<rectangle x1="0.39" y1="2" x2="0.88" y2="3.1" layer="51"/>
<rectangle x1="-0.88" y1="2" x2="-0.39" y2="3.1" layer="51"/>
<rectangle x1="-2.15" y1="2" x2="-1.66" y2="3.1" layer="51"/>
<rectangle x1="0.39" y1="-3.1" x2="0.88" y2="-2" layer="51"/>
<rectangle x1="1.66" y1="-3.1" x2="2.15" y2="-2" layer="51"/>
<rectangle x1="2.93" y1="-3.1" x2="3.42" y2="-2" layer="51"/>
<rectangle x1="4.2" y1="-3.1" x2="4.69" y2="-2" layer="51"/>
<rectangle x1="4.2" y1="2" x2="4.69" y2="3.1" layer="51"/>
<rectangle x1="2.93" y1="2" x2="3.42" y2="3.1" layer="51"/>
<rectangle x1="-3.42" y1="2" x2="-2.93" y2="3.1" layer="51"/>
<rectangle x1="-4.69" y1="2" x2="-4.2" y2="3.1" layer="51"/>
</package>
<package name="4-PIN-ZIF">
<description>&lt;b&gt;8 DIL Package&lt;/b&gt; 4 Pads&lt;p&gt;
Motien Technology Co.,Ltd.&lt;br&gt;
Source: va-serie.pdf.pdf</description>
<wire x1="-3.7084" y1="-1.1684" x2="-3.7084" y2="3.7084" width="0.2032" layer="21"/>
<wire x1="-3.7084" y1="3.7084" x2="3.7084" y2="3.7084" width="0.2032" layer="21"/>
<wire x1="3.7084" y1="3.7084" x2="3.7084" y2="-1.1684" width="0.2032" layer="21"/>
<wire x1="3.7084" y1="-1.1684" x2="-3.7084" y2="-1.1684" width="0.2032" layer="21"/>
<circle x="-2.6797" y="-0.2667" radius="0.6477" width="0" layer="21"/>
<pad name="4" x="-2.54" y="2.54" drill="0.7" diameter="1.27"/>
<pad name="1" x="2.54" y="2.54" drill="0.7" diameter="1.27"/>
<pad name="2" x="1.27" y="0" drill="0.7" diameter="1.27"/>
<pad name="3" x="-1.27" y="0" drill="0.7" diameter="1.27"/>
<text x="-3.175" y="-3.175" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.81" y="-0.635" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="DIL4-SMD">
<description>&lt;b&gt;Dual  In Line SMD&lt;/b&gt; 4 pol.&lt;p&gt;
Source: LITE-ON ELECTRONICS, LTV816.pdf</description>
<wire x1="2.315" y1="3.18" x2="2.315" y2="-2.164" width="0.1524" layer="21"/>
<wire x1="2.315" y1="-2.164" x2="2.315" y2="-3.18" width="0.1524" layer="21"/>
<wire x1="-2.315" y1="3.18" x2="2.315" y2="3.18" width="0.1524" layer="21"/>
<wire x1="2.315" y1="-3.18" x2="-2.315" y2="-3.18" width="0.1524" layer="21"/>
<wire x1="-2.315" y1="-3.18" x2="-2.315" y2="3.18" width="0.1524" layer="21"/>
<wire x1="2.315" y1="-2.164" x2="-2.315" y2="-2.164" width="0.1524" layer="21"/>
<smd name="1" x="-1.27" y="-4.77" dx="1.6" dy="2" layer="1"/>
<smd name="2" x="1.27" y="-4.77" dx="1.6" dy="2" layer="1"/>
<smd name="3" x="1.27" y="4.77" dx="1.6" dy="2" layer="1" rot="R180"/>
<smd name="4" x="-1.27" y="4.77" dx="1.6" dy="2" layer="1" rot="R180"/>
<text x="-2.54" y="-3.175" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.81" y="-3.175" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.875" y1="-5.15" x2="-0.65" y2="-3.2" layer="51"/>
<rectangle x1="0.665" y1="-5.15" x2="1.89" y2="-3.2" layer="51"/>
<rectangle x1="0.65" y1="3.2" x2="1.875" y2="5.15" layer="51" rot="R180"/>
<rectangle x1="-1.89" y1="3.2" x2="-0.665" y2="5.15" layer="51" rot="R180"/>
</package>
<package name="DIL04">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="2.54" y1="2.921" x2="-2.54" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-2.921" x2="2.54" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="2.54" y1="2.921" x2="2.54" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="2.921" x2="-2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-2.921" x2="-2.54" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.016" x2="-2.54" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-1.27" y="-3.81" drill="0.8128" shape="offset" rot="R270"/>
<pad name="2" x="1.27" y="-3.81" drill="0.8128" shape="offset" rot="R270"/>
<pad name="3" x="1.27" y="3.81" drill="0.8128" shape="offset" rot="R90"/>
<pad name="4" x="-1.27" y="3.81" drill="0.8128" shape="offset" rot="R90"/>
<text x="4.191" y="-2.921" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<text x="-2.921" y="-2.667" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
</package>
<package name="VTX-214-003-105">
<wire x1="-9.99" y1="12.51" x2="-6.815" y2="12.51" width="0.254" layer="21"/>
<wire x1="-6.815" y1="12.51" x2="-6.815" y2="-5.27" width="0.254" layer="21"/>
<wire x1="-4.91" y1="12.51" x2="-4.91" y2="-5.27" width="0.254" layer="21"/>
<wire x1="-4.91" y1="-5.27" x2="-6.815" y2="-5.27" width="0.254" layer="21"/>
<wire x1="-3.64" y1="12.51" x2="-3.64" y2="-5.27" width="0.254" layer="21"/>
<wire x1="-2.37" y1="6.16" x2="-2.37" y2="1.08" width="0.254" layer="21"/>
<wire x1="-2.37" y1="1.08" x2="2.71" y2="1.08" width="0.254" layer="21"/>
<wire x1="-2.37" y1="6.16" x2="2.71" y2="6.16" width="0.254" layer="21"/>
<wire x1="-6.815" y1="12.51" x2="-4.91" y2="12.51" width="0.254" layer="21"/>
<wire x1="-6.815" y1="-5.27" x2="-9.99" y2="-5.27" width="0.254" layer="21"/>
<wire x1="11.557" y1="-14.986" x2="12.065" y2="-14.478" width="0.254" layer="21" curve="90"/>
<wire x1="-17.526" y1="-12.954" x2="9.906" y2="-12.954" width="0.254" layer="21"/>
<wire x1="-17.526" y1="20.574" x2="-17.526" y2="-12.954" width="0.254" layer="21"/>
<wire x1="-17.526" y1="20.574" x2="9.906" y2="20.574" width="0.254" layer="21"/>
<wire x1="9.906" y1="-12.954" x2="9.906" y2="20.574" width="0.254" layer="21"/>
<circle x="-8.085" y="-4.381" radius="0.254" width="0.254" layer="21"/>
<circle x="0.805" y="1.969" radius="0.254" width="0.254" layer="21"/>
<circle x="-10.625" y="-5.27" radius="0.635" width="0.254" layer="21"/>
<circle x="-10.625" y="12.51" radius="0.635" width="0.254" layer="21"/>
<circle x="3.345" y="1.08" radius="0.635" width="0.254" layer="21"/>
<circle x="3.345" y="6.16" radius="0.635" width="0.254" layer="21"/>
<pad name="3" x="6.4968" y="-1.0038" drill="1.3208" diameter="3.175" shape="octagon"/>
<pad name="4" x="6.4968" y="9.0038" drill="1.3208" diameter="3.175" shape="octagon"/>
<pad name="2" x="-13.4968" y="-6.0076" drill="1.3208" diameter="3.81" shape="octagon"/>
<pad name="1" x="-13.4968" y="14.0076" drill="1.3208" diameter="3.81" shape="octagon"/>
<text x="-17.145" y="21.59" size="2.54" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.35" y="-10.795" size="2.54" layer="27" ratio="10">&gt;VALUE</text>
<text x="-7.45" y="0.445" size="1.778" layer="21" ratio="10" rot="R90">MAINS</text>
<text x="2.075" y="2.35" size="1.778" layer="21" ratio="10">O/P</text>
<text x="-4.445" y="13.97" size="2.54" layer="21" ratio="10"></text>
<wire x1="0.17" y1="9.97" x2="0.17" y2="7.43" width="0.127" layer="21"/>
<wire x1="-1.1" y1="8.7" x2="1.44" y2="8.7" width="0.127" layer="21"/>
<wire x1="-1.1" y1="-1.46" x2="1.44" y2="-1.46" width="0.127" layer="21"/>
</package>
<package name="RLB0914-4R7ML">
<circle x="0" y="0" radius="4.4" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.9" diameter="1.4224"/>
<pad name="2" x="2.5" y="0" drill="0.9" diameter="1.4224"/>
<text x="-4.5056" y="4.6326" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.5056" y="-6.4106" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="S216S01F">
<description>&lt;b&gt;SOLID STATE RELAY&lt;/b&gt; NAiS&lt;p&gt;
Source: http://www.mew-europe.com/.. en_ds_61601_0000.pdf</description>
<pad name="1" x="-8.89" y="0" drill="1.2"/>
<pad name="2" x="-3.81" y="0" drill="1.2"/>
<pad name="3" x="3.81" y="0" drill="1.2"/>
<pad name="4" x="6.35" y="0" drill="1.2"/>
<text x="-11.43" y="-2.54" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.81" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<wire x1="-12.7" y1="-2.54" x2="-12.7" y2="2.54" width="0.127" layer="21"/>
<wire x1="-12.7" y1="2.54" x2="10.16" y2="2.54" width="0.127" layer="21"/>
<wire x1="10.16" y1="2.54" x2="10.16" y2="-2.54" width="0.127" layer="21"/>
<wire x1="10.16" y1="-2.54" x2="-12.7" y2="-2.54" width="0.127" layer="21"/>
</package>
<package name="TO92">
<description>&lt;b&gt;TO 92&lt;/b&gt;</description>
<wire x1="-2.0946" y1="-1.651" x2="-2.6549" y2="-0.254" width="0.127" layer="21" curve="-32.781"/>
<wire x1="-2.6549" y1="-0.254" x2="-0.7863" y2="2.5485" width="0.127" layer="21" curve="-78.3185"/>
<wire x1="0.7863" y1="2.5484" x2="2.0945" y2="-1.651" width="0.127" layer="21" curve="-111.1"/>
<wire x1="-2.0945" y1="-1.651" x2="2.0945" y2="-1.651" width="0.127" layer="21"/>
<wire x1="-2.2537" y1="-0.254" x2="-0.2863" y2="-0.254" width="0.127" layer="51"/>
<wire x1="-2.6549" y1="-0.254" x2="-2.2537" y2="-0.254" width="0.127" layer="21"/>
<wire x1="-0.2863" y1="-0.254" x2="0.2863" y2="-0.254" width="0.127" layer="21"/>
<wire x1="2.2537" y1="-0.254" x2="2.6549" y2="-0.254" width="0.127" layer="21"/>
<wire x1="0.2863" y1="-0.254" x2="2.2537" y2="-0.254" width="0.127" layer="51"/>
<wire x1="-0.7863" y1="2.5485" x2="0.7863" y2="2.5485" width="0.127" layer="51" curve="-34.2936"/>
<pad name="1" x="1.27" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="0" y="1.905" drill="0.8128" shape="octagon"/>
<pad name="3" x="-1.27" y="0" drill="0.8128" shape="octagon"/>
<text x="3.175" y="0.635" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="3.175" y="-1.27" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-0.635" y="0.635" size="1.27" layer="51" ratio="10">2</text>
<text x="-2.159" y="0" size="1.27" layer="51" ratio="10">3</text>
<text x="1.143" y="0" size="1.27" layer="51" ratio="10">1</text>
</package>
<package name="PHOTON">
<pad name="1" x="1.27" y="32.258" drill="1.016" diameter="1.8796"/>
<pad name="2" x="1.27" y="29.718" drill="1.016" diameter="1.8796"/>
<pad name="3" x="1.27" y="27.178" drill="1.016" diameter="1.8796"/>
<pad name="4" x="1.27" y="24.638" drill="1.016" diameter="1.8796"/>
<pad name="5" x="1.27" y="22.098" drill="1.016" diameter="1.8796"/>
<pad name="6" x="1.27" y="19.558" drill="1.016" diameter="1.8796"/>
<pad name="7" x="1.27" y="17.018" drill="1.016" diameter="1.8796"/>
<pad name="8" x="1.27" y="14.478" drill="1.016" diameter="1.8796"/>
<pad name="9" x="1.27" y="11.938" drill="1.016" diameter="1.8796"/>
<pad name="10" x="1.27" y="9.398" drill="1.016" diameter="1.8796"/>
<pad name="11" x="1.27" y="6.858" drill="1.016" diameter="1.8796"/>
<pad name="12" x="1.27" y="4.318" drill="1.016" diameter="1.8796"/>
<text x="2.54" y="-1.778" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<rectangle x1="1.016" y1="16.764" x2="1.524" y2="17.272" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="19.304" x2="1.524" y2="19.812" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="21.844" x2="1.524" y2="22.352" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="24.384" x2="1.524" y2="24.892" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="26.924" x2="1.524" y2="27.432" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="29.464" x2="1.524" y2="29.972" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="32.004" x2="1.524" y2="32.512" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="14.224" x2="1.524" y2="14.732" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="11.684" x2="1.524" y2="12.192" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="9.144" x2="1.524" y2="9.652" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="6.604" x2="1.524" y2="7.112" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="4.064" x2="1.524" y2="4.572" layer="51" rot="R270"/>
<pad name="13" x="19.05" y="4.318" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="14" x="19.05" y="6.858" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="15" x="19.05" y="9.398" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="16" x="19.05" y="11.938" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="17" x="19.05" y="14.478" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="18" x="19.05" y="17.018" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="19" x="19.05" y="19.558" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="20" x="19.05" y="22.098" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="21" x="19.05" y="24.638" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="22" x="19.05" y="27.178" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="23" x="19.05" y="29.718" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="24" x="19.05" y="32.258" drill="1.016" diameter="1.8796" rot="R180"/>
<text x="2.54" y="-3.302" size="1.27" layer="27" rot="SR0">&gt;VALUE</text>
<rectangle x1="18.796" y1="19.304" x2="19.304" y2="19.812" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="16.764" x2="19.304" y2="17.272" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="14.224" x2="19.304" y2="14.732" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="11.684" x2="19.304" y2="12.192" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="9.144" x2="19.304" y2="9.652" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="6.604" x2="19.304" y2="7.112" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="4.064" x2="19.304" y2="4.572" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="21.844" x2="19.304" y2="22.352" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="24.384" x2="19.304" y2="24.892" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="26.924" x2="19.304" y2="27.432" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="29.464" x2="19.304" y2="29.972" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="32.004" x2="19.304" y2="32.512" layer="51" rot="R90"/>
<wire x1="20.32" y1="33.528" x2="20.32" y2="36.576" width="0.3048" layer="21"/>
<wire x1="0" y1="36.576" x2="0" y2="33.528" width="0.3048" layer="21"/>
<wire x1="6.096" y1="38.481" x2="6.096" y2="36.576" width="0.3048" layer="21"/>
<wire x1="14.224" y1="36.576" x2="14.224" y2="38.481" width="0.3048" layer="21"/>
<wire x1="14.224" y1="38.481" x2="6.096" y2="38.481" width="0.3048" layer="21"/>
<wire x1="0" y1="36.576" x2="6.096" y2="36.576" width="0.3048" layer="21"/>
<wire x1="14.224" y1="36.576" x2="20.32" y2="36.576" width="0.3048" layer="21"/>
<wire x1="0" y1="3.048" x2="1.524" y2="0" width="0.3048" layer="21"/>
<wire x1="1.524" y1="0" x2="18.796" y2="0" width="0.3048" layer="21"/>
<wire x1="18.796" y1="0" x2="20.32" y2="3.048" width="0.3048" layer="21"/>
<wire x1="0" y1="33.528" x2="0" y2="3.048" width="0.3048" layer="21"/>
<wire x1="0" y1="3.048" x2="2.54" y2="3.048" width="0.3048" layer="21"/>
<wire x1="2.54" y1="3.048" x2="2.54" y2="33.528" width="0.3048" layer="21"/>
<wire x1="2.54" y1="33.528" x2="0" y2="33.528" width="0.3048" layer="21"/>
<wire x1="20.32" y1="33.528" x2="20.32" y2="3.048" width="0.3048" layer="21"/>
<wire x1="20.32" y1="3.048" x2="17.78" y2="3.048" width="0.3048" layer="21"/>
<wire x1="17.78" y1="33.528" x2="20.32" y2="33.528" width="0.3048" layer="21"/>
<wire x1="0" y1="3.048" x2="1.524" y2="0" width="0.3048" layer="51"/>
<wire x1="1.524" y1="0" x2="18.796" y2="0" width="0.3048" layer="51"/>
<wire x1="18.796" y1="0" x2="20.32" y2="3.048" width="0.3048" layer="51"/>
<text x="19.05" y="4.064" size="0.6096" layer="51" font="vector">13</text>
<text x="3.302" y="0.381" size="0.6096" layer="51" font="vector">GROUND PLANE
AND SIGNAL KEEP OUT
RECOMMENDED ON ALL LAYERS</text>
<wire x1="1.524" y1="3.048" x2="1.524" y2="-3.556" width="0.127" layer="51" style="shortdash"/>
<wire x1="1.524" y1="-3.556" x2="18.796" y2="-3.556" width="0.127" layer="51" style="shortdash"/>
<wire x1="18.796" y1="-3.556" x2="18.796" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="18.796" y1="3.048" x2="17.78" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="17.78" y1="3.048" x2="17.78" y2="5.588" width="0.127" layer="51" style="shortdash"/>
<wire x1="17.78" y1="5.588" x2="2.54" y2="5.588" width="0.127" layer="51" style="shortdash"/>
<wire x1="2.54" y1="5.588" x2="2.54" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="2.54" y1="3.048" x2="1.524" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="17.78" y1="3.048" x2="17.78" y2="33.528" width="0.3048" layer="21"/>
<wire x1="0" y1="3.048" x2="0" y2="33.528" width="0.3048" layer="51"/>
<wire x1="0" y1="33.528" x2="0" y2="36.576" width="0.3048" layer="51"/>
<wire x1="0" y1="36.576" x2="6.096" y2="36.576" width="0.3048" layer="51"/>
<wire x1="6.096" y1="36.576" x2="6.096" y2="38.481" width="0.3048" layer="51"/>
<wire x1="6.096" y1="38.481" x2="14.224" y2="38.481" width="0.3048" layer="51"/>
<wire x1="14.224" y1="38.481" x2="14.224" y2="36.576" width="0.3048" layer="51"/>
<wire x1="14.224" y1="36.576" x2="20.32" y2="36.576" width="0.3048" layer="51"/>
<wire x1="20.32" y1="36.576" x2="20.32" y2="33.528" width="0.3048" layer="51"/>
<rectangle x1="1.524" y1="-3.556" x2="18.796" y2="3.048" layer="39"/>
<rectangle x1="2.54" y1="3.048" x2="17.78" y2="5.588" layer="39"/>
<rectangle x1="2.54" y1="3.048" x2="17.78" y2="5.588" layer="40"/>
<rectangle x1="1.524" y1="-3.556" x2="18.796" y2="3.048" layer="40"/>
<text x="2.794" y="32.004" size="0.6096" layer="51" font="vector">1</text>
<text x="2.794" y="4.064" size="0.6096" layer="51" font="vector">12</text>
<text x="16.51" y="4.064" size="0.6096" layer="51" font="vector">13</text>
<text x="16.51" y="32.004" size="0.6096" layer="51" font="vector">24</text>
<wire x1="20.32" y1="33.528" x2="20.32" y2="3.048" width="0.3048" layer="51"/>
<wire x1="0" y1="33.528" x2="2.54" y2="33.528" width="0.3048" layer="51"/>
<wire x1="2.54" y1="33.528" x2="2.54" y2="3.048" width="0.3048" layer="51"/>
<wire x1="2.54" y1="3.048" x2="0" y2="3.048" width="0.3048" layer="51"/>
<wire x1="20.32" y1="3.048" x2="17.78" y2="3.048" width="0.3048" layer="51"/>
<wire x1="17.78" y1="3.048" x2="17.78" y2="33.528" width="0.3048" layer="51"/>
<wire x1="17.78" y1="33.528" x2="20.32" y2="33.528" width="0.3048" layer="51"/>
</package>
<package name="PHOTON_STACKABLE">
<pad name="1" x="1.27" y="32.258" drill="1.016" diameter="1.8796"/>
<pad name="2" x="1.27" y="29.718" drill="1.016" diameter="1.8796"/>
<pad name="3" x="1.27" y="27.178" drill="1.016" diameter="1.8796"/>
<pad name="4" x="1.27" y="24.638" drill="1.016" diameter="1.8796"/>
<pad name="5" x="1.27" y="22.098" drill="1.016" diameter="1.8796"/>
<pad name="6" x="1.27" y="19.558" drill="1.016" diameter="1.8796"/>
<pad name="7" x="1.27" y="17.018" drill="1.016" diameter="1.8796"/>
<pad name="8" x="1.27" y="14.478" drill="1.016" diameter="1.8796"/>
<pad name="9" x="1.27" y="11.938" drill="1.016" diameter="1.8796"/>
<pad name="10" x="1.27" y="9.398" drill="1.016" diameter="1.8796"/>
<pad name="11" x="1.27" y="6.858" drill="1.016" diameter="1.8796"/>
<pad name="12" x="1.27" y="4.318" drill="1.016" diameter="1.8796"/>
<text x="2.54" y="-1.778" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<rectangle x1="1.016" y1="16.764" x2="1.524" y2="17.272" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="19.304" x2="1.524" y2="19.812" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="21.844" x2="1.524" y2="22.352" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="24.384" x2="1.524" y2="24.892" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="26.924" x2="1.524" y2="27.432" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="29.464" x2="1.524" y2="29.972" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="32.004" x2="1.524" y2="32.512" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="14.224" x2="1.524" y2="14.732" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="11.684" x2="1.524" y2="12.192" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="9.144" x2="1.524" y2="9.652" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="6.604" x2="1.524" y2="7.112" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="4.064" x2="1.524" y2="4.572" layer="51" rot="R270"/>
<pad name="13" x="19.05" y="4.318" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="14" x="19.05" y="6.858" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="15" x="19.05" y="9.398" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="16" x="19.05" y="11.938" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="17" x="19.05" y="14.478" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="18" x="19.05" y="17.018" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="19" x="19.05" y="19.558" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="20" x="19.05" y="22.098" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="21" x="19.05" y="24.638" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="22" x="19.05" y="27.178" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="23" x="19.05" y="29.718" drill="1.016" diameter="1.8796" rot="R180"/>
<pad name="24" x="19.05" y="32.258" drill="1.016" diameter="1.8796" rot="R180"/>
<text x="2.54" y="-3.302" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="18.796" y1="19.304" x2="19.304" y2="19.812" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="16.764" x2="19.304" y2="17.272" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="14.224" x2="19.304" y2="14.732" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="11.684" x2="19.304" y2="12.192" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="9.144" x2="19.304" y2="9.652" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="6.604" x2="19.304" y2="7.112" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="4.064" x2="19.304" y2="4.572" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="21.844" x2="19.304" y2="22.352" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="24.384" x2="19.304" y2="24.892" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="26.924" x2="19.304" y2="27.432" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="29.464" x2="19.304" y2="29.972" layer="51" rot="R90"/>
<rectangle x1="18.796" y1="32.004" x2="19.304" y2="32.512" layer="51" rot="R90"/>
<wire x1="22.86" y1="33.528" x2="20.32" y2="33.528" width="0.3048" layer="21"/>
<wire x1="20.32" y1="33.528" x2="20.32" y2="36.576" width="0.3048" layer="21"/>
<wire x1="0" y1="36.576" x2="0" y2="33.528" width="0.3048" layer="21"/>
<wire x1="6.096" y1="38.481" x2="6.096" y2="36.576" width="0.3048" layer="21"/>
<wire x1="14.224" y1="36.576" x2="14.224" y2="38.481" width="0.3048" layer="21"/>
<wire x1="14.224" y1="38.481" x2="6.096" y2="38.481" width="0.3048" layer="21"/>
<wire x1="0" y1="36.576" x2="6.096" y2="36.576" width="0.3048" layer="21"/>
<wire x1="14.224" y1="36.576" x2="20.32" y2="36.576" width="0.3048" layer="21"/>
<wire x1="0" y1="3.048" x2="1.524" y2="0" width="0.3048" layer="21"/>
<wire x1="1.524" y1="0" x2="18.796" y2="0" width="0.3048" layer="21"/>
<wire x1="18.796" y1="0" x2="20.32" y2="3.048" width="0.3048" layer="21"/>
<pad name="@1" x="-1.27" y="32.258" drill="1.016" diameter="1.8796"/>
<pad name="@2" x="-1.27" y="29.718" drill="1.016" diameter="1.8796"/>
<pad name="@3" x="-1.27" y="27.178" drill="1.016" diameter="1.8796"/>
<pad name="@4" x="-1.27" y="24.638" drill="1.016" diameter="1.8796"/>
<pad name="@5" x="-1.27" y="22.098" drill="1.016" diameter="1.8796"/>
<pad name="@6" x="-1.27" y="19.558" drill="1.016" diameter="1.8796"/>
<pad name="@7" x="-1.27" y="17.018" drill="1.016" diameter="1.8796"/>
<pad name="@8" x="-1.27" y="14.478" drill="1.016" diameter="1.8796"/>
<pad name="@9" x="-1.27" y="11.938" drill="1.016" diameter="1.8796"/>
<pad name="@10" x="-1.27" y="9.398" drill="1.016" diameter="1.8796"/>
<pad name="@11" x="-1.27" y="6.858" drill="1.016" diameter="1.8796"/>
<pad name="@12" x="-1.27" y="4.318" drill="1.016" diameter="1.8796"/>
<pad name="@13" x="16.51" y="4.318" drill="1.016" diameter="1.8796"/>
<pad name="@14" x="16.51" y="6.858" drill="1.016" diameter="1.8796"/>
<pad name="@15" x="16.51" y="9.398" drill="1.016" diameter="1.8796"/>
<pad name="@16" x="16.51" y="11.938" drill="1.016" diameter="1.8796"/>
<pad name="@17" x="16.51" y="14.478" drill="1.016" diameter="1.8796"/>
<pad name="@18" x="16.51" y="17.018" drill="1.016" diameter="1.8796"/>
<pad name="@19" x="16.51" y="19.558" drill="1.016" diameter="1.8796"/>
<pad name="@20" x="16.51" y="22.098" drill="1.016" diameter="1.8796"/>
<pad name="@21" x="16.51" y="24.638" drill="1.016" diameter="1.8796"/>
<pad name="@22" x="16.51" y="27.178" drill="1.016" diameter="1.8796"/>
<pad name="@23" x="16.51" y="29.718" drill="1.016" diameter="1.8796"/>
<pad name="@24" x="16.51" y="32.258" drill="1.016" diameter="1.8796"/>
<pad name="#1" x="3.81" y="32.258" drill="1.016" diameter="1.8796"/>
<pad name="#2" x="3.81" y="29.718" drill="1.016" diameter="1.8796"/>
<pad name="#3" x="3.81" y="27.178" drill="1.016" diameter="1.8796"/>
<pad name="#4" x="3.81" y="24.638" drill="1.016" diameter="1.8796"/>
<pad name="#5" x="3.81" y="22.098" drill="1.016" diameter="1.8796"/>
<pad name="#6" x="3.81" y="19.558" drill="1.016" diameter="1.8796"/>
<pad name="#7" x="3.81" y="17.018" drill="1.016" diameter="1.8796"/>
<pad name="#8" x="3.81" y="14.478" drill="1.016" diameter="1.8796"/>
<pad name="#9" x="3.81" y="11.938" drill="1.016" diameter="1.8796"/>
<pad name="#10" x="3.81" y="9.398" drill="1.016" diameter="1.8796"/>
<pad name="#11" x="3.81" y="6.858" drill="1.016" diameter="1.8796"/>
<pad name="#12" x="3.81" y="4.318" drill="1.016" diameter="1.8796"/>
<pad name="#13" x="21.59" y="4.318" drill="1.016" diameter="1.8796"/>
<pad name="#14" x="21.59" y="6.858" drill="1.016" diameter="1.8796"/>
<pad name="#15" x="21.59" y="9.398" drill="1.016" diameter="1.8796"/>
<pad name="#16" x="21.59" y="11.938" drill="1.016" diameter="1.8796"/>
<pad name="#17" x="21.59" y="14.478" drill="1.016" diameter="1.8796"/>
<pad name="#18" x="21.59" y="17.018" drill="1.016" diameter="1.8796"/>
<pad name="#19" x="21.59" y="19.558" drill="1.016" diameter="1.8796"/>
<pad name="#20" x="21.59" y="22.098" drill="1.016" diameter="1.8796"/>
<pad name="#21" x="21.59" y="24.638" drill="1.016" diameter="1.8796"/>
<pad name="#22" x="21.59" y="27.178" drill="1.016" diameter="1.8796"/>
<pad name="#23" x="21.59" y="29.718" drill="1.016" diameter="1.8796"/>
<pad name="#24" x="21.59" y="32.258" drill="1.016" diameter="1.8796"/>
<wire x1="0" y1="33.528" x2="5.08" y2="33.528" width="0.3048" layer="21"/>
<wire x1="5.08" y1="33.528" x2="5.08" y2="3.048" width="0.3048" layer="21"/>
<wire x1="5.08" y1="3.048" x2="0" y2="3.048" width="0.3048" layer="21"/>
<wire x1="0" y1="3.048" x2="-2.54" y2="3.048" width="0.3048" layer="21"/>
<wire x1="-2.54" y1="3.048" x2="-2.54" y2="33.528" width="0.3048" layer="21"/>
<wire x1="-2.54" y1="33.528" x2="0" y2="33.528" width="0.3048" layer="21"/>
<wire x1="20.32" y1="33.528" x2="15.24" y2="33.528" width="0.3048" layer="21"/>
<wire x1="15.24" y1="33.528" x2="15.24" y2="3.048" width="0.3048" layer="21"/>
<wire x1="15.24" y1="3.048" x2="20.32" y2="3.048" width="0.3048" layer="21"/>
<wire x1="20.32" y1="3.048" x2="22.86" y2="3.048" width="0.3048" layer="21"/>
<wire x1="22.86" y1="3.048" x2="22.86" y2="33.528" width="0.3048" layer="21"/>
<text x="5.588" y="32.004" size="0.6096" layer="51" font="vector">1</text>
<text x="5.334" y="4.064" size="0.6096" layer="51" font="vector">12</text>
<text x="13.97" y="4.064" size="0.6096" layer="51" font="vector">13</text>
<text x="13.97" y="32.004" size="0.6096" layer="51" font="vector">24</text>
<text x="3.302" y="0.254" size="0.6096" layer="51" font="vector">GROUND PLANE
AND SIGNAL KEEP OUT
RECOMMENDED ON ALL LAYERS</text>
<wire x1="1.524" y1="3.048" x2="1.524" y2="0" width="0.127" layer="51" style="shortdash"/>
<wire x1="1.524" y1="0" x2="1.524" y2="-3.556" width="0.127" layer="51" style="shortdash"/>
<wire x1="1.524" y1="-3.556" x2="18.796" y2="-3.556" width="0.127" layer="51" style="shortdash"/>
<wire x1="18.796" y1="-3.556" x2="18.796" y2="0" width="0.127" layer="51" style="shortdash"/>
<wire x1="18.796" y1="0" x2="18.796" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="18.796" y1="3.048" x2="15.24" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="15.24" y1="3.048" x2="15.24" y2="5.588" width="0.127" layer="51" style="shortdash"/>
<wire x1="15.24" y1="5.588" x2="5.08" y2="5.588" width="0.127" layer="51" style="shortdash"/>
<wire x1="5.08" y1="5.588" x2="5.08" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="5.08" y1="3.048" x2="2.54" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<rectangle x1="1.524" y1="-3.556" x2="18.796" y2="3.048" layer="39"/>
<rectangle x1="1.524" y1="-3.556" x2="18.796" y2="3.048" layer="40"/>
<rectangle x1="5.08" y1="3.048" x2="15.24" y2="5.588" layer="39"/>
<rectangle x1="5.08" y1="3.048" x2="15.24" y2="5.588" layer="40"/>
<wire x1="2.54" y1="3.048" x2="1.524" y2="3.048" width="0.127" layer="51" style="shortdash"/>
<wire x1="6.096" y1="36.576" x2="6.096" y2="38.481" width="0.3048" layer="51"/>
<wire x1="6.096" y1="38.481" x2="14.224" y2="38.481" width="0.3048" layer="51"/>
<wire x1="14.224" y1="38.481" x2="14.224" y2="36.576" width="0.3048" layer="51"/>
<wire x1="14.224" y1="36.576" x2="20.32" y2="36.576" width="0.3048" layer="51"/>
<wire x1="20.32" y1="36.576" x2="20.32" y2="33.528" width="0.3048" layer="51"/>
<wire x1="20.32" y1="33.528" x2="20.32" y2="3.048" width="0.3048" layer="51"/>
<wire x1="20.32" y1="3.048" x2="18.796" y2="0" width="0.3048" layer="51"/>
<wire x1="18.796" y1="0" x2="1.524" y2="0" width="0.3048" layer="51"/>
<wire x1="1.524" y1="0" x2="0" y2="3.048" width="0.3048" layer="51"/>
<wire x1="0" y1="3.048" x2="0" y2="33.528" width="0.3048" layer="51"/>
<wire x1="0" y1="33.528" x2="0" y2="36.576" width="0.3048" layer="51"/>
<wire x1="0" y1="36.576" x2="6.096" y2="36.576" width="0.3048" layer="51"/>
<wire x1="20.32" y1="33.528" x2="17.78" y2="33.528" width="0.3048" layer="51"/>
<wire x1="17.78" y1="33.528" x2="17.78" y2="3.048" width="0.3048" layer="51"/>
<wire x1="17.78" y1="3.048" x2="20.32" y2="3.048" width="0.3048" layer="51"/>
<wire x1="0" y1="3.048" x2="2.54" y2="3.048" width="0.3048" layer="51"/>
<wire x1="2.54" y1="3.048" x2="2.54" y2="33.528" width="0.3048" layer="51"/>
<wire x1="2.54" y1="33.528" x2="0" y2="33.528" width="0.3048" layer="51"/>
</package>
<package name="SH32">
<description>&lt;b&gt;FUSE HOLDER&lt;/b&gt;&lt;p&gt; 6 x 32 mm, SH contact, SHH3N Schukat / Wickmann 102071 (Buerklin)</description>
<wire x1="9.017" y1="3.81" x2="9.525" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="3.556" x2="8.89" y2="3.556" width="0.1524" layer="21"/>
<wire x1="8.89" y1="3.556" x2="9.017" y2="3.556" width="0.1524" layer="21"/>
<wire x1="9.017" y1="-3.81" x2="9.017" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="9.017" y1="-3.556" x2="8.89" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="8.89" y1="-3.556" x2="-8.89" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="9.017" y1="3.556" x2="9.017" y2="3.81" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-3.81" x2="9.525" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-3.81" x2="9.017" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-4.445" x2="16.764" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="16.764" y1="4.445" x2="9.525" y2="4.445" width="0.1524" layer="21"/>
<wire x1="9.525" y1="3.81" x2="9.525" y2="4.445" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-3.81" x2="9.525" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="9.525" y1="3.81" x2="9.525" y2="2.794" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-2.794" x2="16.002" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.794" x2="16.002" y2="2.794" width="0.1524" layer="21"/>
<wire x1="16.764" y1="-2.032" x2="16.764" y2="2.032" width="0.1524" layer="51"/>
<wire x1="16.002" y1="-2.032" x2="16.002" y2="2.032" width="0.1524" layer="51"/>
<wire x1="9.017" y1="-2.032" x2="9.017" y2="0" width="0.1524" layer="51"/>
<wire x1="16.764" y1="-2.032" x2="16.764" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="16.764" y1="-2.794" x2="16.764" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="16.002" y1="-2.032" x2="16.002" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="16.002" y1="-2.794" x2="16.764" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="16.764" y1="4.445" x2="16.764" y2="2.794" width="0.1524" layer="21"/>
<wire x1="16.764" y1="2.794" x2="16.764" y2="2.032" width="0.1524" layer="21"/>
<wire x1="16.002" y1="2.032" x2="16.002" y2="2.794" width="0.1524" layer="21"/>
<wire x1="16.002" y1="2.794" x2="16.764" y2="2.794" width="0.1524" layer="21"/>
<wire x1="9.017" y1="2.032" x2="9.017" y2="3.556" width="0.1524" layer="21"/>
<wire x1="9.017" y1="-2.032" x2="9.017" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="9.017" y1="0" x2="6.985" y2="0" width="0.0508" layer="51"/>
<wire x1="9.017" y1="0" x2="9.017" y2="2.032" width="0.1524" layer="51"/>
<wire x1="-9.017" y1="-3.81" x2="-9.525" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="8.89" y1="-3.556" x2="-9.017" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="-9.017" y1="3.81" x2="-9.017" y2="3.556" width="0.1524" layer="21"/>
<wire x1="-9.017" y1="3.556" x2="8.89" y2="3.556" width="0.1524" layer="21"/>
<wire x1="-9.017" y1="-3.556" x2="-9.017" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="3.81" x2="-9.525" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="3.81" x2="-9.017" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="4.445" x2="-16.764" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="-4.445" x2="-9.525" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-3.81" x2="-9.525" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="3.81" x2="-9.525" y2="2.794" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-3.81" x2="-9.525" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.794" x2="-16.002" y2="2.794" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.794" x2="-16.002" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="2.032" x2="-16.764" y2="-2.032" width="0.1524" layer="51"/>
<wire x1="-16.002" y1="2.032" x2="-16.002" y2="-2.032" width="0.1524" layer="51"/>
<wire x1="-9.017" y1="2.032" x2="-9.017" y2="0" width="0.1524" layer="51"/>
<wire x1="-16.764" y1="2.032" x2="-16.764" y2="2.794" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="2.794" x2="-16.764" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-16.002" y1="2.032" x2="-16.002" y2="2.794" width="0.1524" layer="21"/>
<wire x1="-16.002" y1="2.794" x2="-16.764" y2="2.794" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="-4.445" x2="-16.764" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="-2.794" x2="-16.764" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-16.002" y1="-2.032" x2="-16.002" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-16.002" y1="-2.794" x2="-16.764" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-9.017" y1="-2.032" x2="-9.017" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="-9.017" y1="2.032" x2="-9.017" y2="3.556" width="0.1524" layer="21"/>
<wire x1="-9.017" y1="0" x2="-6.985" y2="0" width="0.0508" layer="51"/>
<wire x1="-9.017" y1="0" x2="-9.017" y2="-2.032" width="0.1524" layer="51"/>
<wire x1="-6.985" y1="0" x2="6.985" y2="0" width="0.0508" layer="21"/>
<pad name="2B" x="16.764" y="0" drill="2.0066" shape="long" rot="R90"/>
<pad name="2A" x="9.144" y="0" drill="2.0066" shape="long" rot="R90"/>
<pad name="1A" x="-16.764" y="0" drill="2.0066" shape="long" rot="R90"/>
<pad name="1B" x="-9.144" y="0" drill="2.0066" shape="long" rot="R90"/>
<text x="-7.62" y="3.937" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-7.62" y="-5.334" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="9.017" y1="-3.81" x2="9.525" y2="-2.159" layer="21"/>
<rectangle x1="9.017" y1="2.159" x2="9.525" y2="3.81" layer="21"/>
<rectangle x1="9.017" y1="-2.159" x2="9.525" y2="2.159" layer="51"/>
<rectangle x1="-9.525" y1="-3.81" x2="-9.017" y2="-2.159" layer="21"/>
<rectangle x1="-9.525" y1="2.159" x2="-9.017" y2="3.81" layer="21"/>
<rectangle x1="-9.525" y1="-2.159" x2="-9.017" y2="2.159" layer="51"/>
</package>
<package name="SOT95P290X145-6N">
<smd name="1" x="-1.1938" y="0.9398" dx="1.4732" dy="0.5588" layer="1"/>
<smd name="2" x="-1.1938" y="0" dx="1.4732" dy="0.5588" layer="1"/>
<smd name="3" x="-1.1938" y="-0.9398" dx="1.4732" dy="0.5588" layer="1"/>
<smd name="4" x="1.1938" y="-0.9398" dx="1.4732" dy="0.5588" layer="1"/>
<smd name="5" x="1.1938" y="0" dx="1.4732" dy="0.5588" layer="1"/>
<smd name="6" x="1.1938" y="0.9398" dx="1.4732" dy="0.5588" layer="1"/>
<wire x1="-2.1844" y1="-1.7526" x2="-2.1844" y2="1.7526" width="0.1524" layer="39"/>
<wire x1="-2.1844" y1="1.7526" x2="2.1844" y2="1.7526" width="0.1524" layer="39"/>
<wire x1="2.1844" y1="1.7526" x2="2.1844" y2="-1.7526" width="0.1524" layer="39"/>
<wire x1="2.1844" y1="-1.7526" x2="-2.1844" y2="-1.7526" width="0.1524" layer="39"/>
<wire x1="-0.254" y1="-1.4986" x2="0.254" y2="-1.4986" width="0.1524" layer="21"/>
<wire x1="0.254" y1="1.4986" x2="-0.254" y2="1.4986" width="0.1524" layer="21"/>
<wire x1="0.127" y1="1.2192" x2="-0.127" y2="1.2192" width="0.1524" layer="21" curve="-48"/>
<text x="-2.032" y="1.3716" size="1.27" layer="21" ratio="6" rot="SR0">*</text>
<wire x1="-0.8636" y1="-1.4986" x2="0.8636" y2="-1.4986" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="-1.4986" x2="0.8636" y2="-1.1938" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="-1.1938" x2="0.8636" y2="-0.6858" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="-0.6858" x2="0.8636" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="-0.254" x2="0.8636" y2="0.254" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="0.254" x2="0.8636" y2="0.6858" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="1.4986" x2="0.3048" y2="1.4986" width="0.1524" layer="51"/>
<wire x1="0.3048" y1="1.4986" x2="-0.3048" y2="1.4986" width="0.1524" layer="51"/>
<wire x1="-0.3048" y1="1.4986" x2="-0.8636" y2="1.4986" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="1.4986" x2="-0.8636" y2="1.1938" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="1.1938" x2="-0.8636" y2="0.6858" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="0.6858" x2="-0.8636" y2="0.254" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="0.254" x2="-0.8636" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="-0.254" x2="-0.8636" y2="-0.6858" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="1.1938" x2="-1.4986" y2="1.1938" width="0.1524" layer="51"/>
<wire x1="-1.4986" y1="1.1938" x2="-1.4986" y2="0.6858" width="0.1524" layer="51"/>
<wire x1="-1.4986" y1="0.6858" x2="-0.8636" y2="0.6858" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="0.254" x2="-1.4986" y2="0.254" width="0.1524" layer="51"/>
<wire x1="-1.4986" y1="0.254" x2="-1.4986" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="-1.4986" y1="-0.254" x2="-0.8636" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="-1.4986" x2="-0.8636" y2="-1.1938" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="-1.1938" x2="-0.8636" y2="-0.6858" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="-0.6858" x2="-1.4986" y2="-0.6858" width="0.1524" layer="51"/>
<wire x1="-1.4986" y1="-0.6858" x2="-1.4986" y2="-1.1938" width="0.1524" layer="51"/>
<wire x1="-1.4986" y1="-1.1938" x2="-0.8636" y2="-1.1938" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="-1.1938" x2="1.4986" y2="-1.1938" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-1.1938" x2="1.4986" y2="-0.6858" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-0.6858" x2="0.8636" y2="-0.6858" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="-0.254" x2="1.4986" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-0.254" x2="1.4986" y2="0.254" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="0.254" x2="0.8636" y2="0.254" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="1.4986" x2="0.8636" y2="1.1938" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="1.1938" x2="0.8636" y2="0.6858" width="0.1524" layer="51"/>
<wire x1="0.8636" y1="0.6858" x2="1.4986" y2="0.6858" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="0.6858" x2="1.4986" y2="1.1938" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="1.1938" x2="0.8636" y2="1.1938" width="0.1524" layer="51"/>
<wire x1="0.3048" y1="1.4986" x2="-0.3048" y2="1.4986" width="0.1524" layer="51" curve="-180"/>
<text x="-2.032" y="1.3716" size="1.27" layer="51" ratio="6" rot="SR0">*</text>
<text x="-4.6228" y="2.413" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-5.6388" y="-4.064" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1500X500X1200">
<pad name="1" x="-12.4968" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<text x="-10.7442" y="6.1722" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-11.5824" y="-6.8326" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
<wire x1="1.7526" y1="-2.9972" x2="-14.2494" y2="-2.9972" width="0.1524" layer="39"/>
<wire x1="-14.2494" y1="-2.9972" x2="-14.2494" y2="2.9972" width="0.1524" layer="39"/>
<wire x1="-14.2494" y1="2.9972" x2="1.7526" y2="2.9972" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="2.9972" x2="1.7526" y2="-2.9972" width="0.1524" layer="39"/>
<wire x1="-13.9954" y1="-2.7432" x2="1.4986" y2="-2.7432" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-2.7432" x2="1.4986" y2="2.7432" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="2.7432" x2="-13.9954" y2="2.7432" width="0.1524" layer="21"/>
<wire x1="-13.9954" y1="2.7432" x2="-13.9954" y2="-2.7432" width="0.1524" layer="21"/>
<wire x1="-13.9954" y1="-2.7432" x2="1.4986" y2="-2.7432" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-2.7432" x2="1.4986" y2="2.7432" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="2.7432" x2="-13.9954" y2="2.7432" width="0.1524" layer="51"/>
<wire x1="-13.9954" y1="2.7432" x2="-13.9954" y2="-2.7432" width="0.1524" layer="51"/>
<text x="-10.7442" y="6.1722" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-11.5824" y="-6.8326" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1500X600X1350">
<pad name="1" x="-12.4968" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="2.0066" y1="-3.5052" x2="-14.5034" y2="-3.5052" width="0.1524" layer="39"/>
<wire x1="-14.5034" y1="-3.5052" x2="-14.5034" y2="3.5052" width="0.1524" layer="39"/>
<wire x1="-14.5034" y1="3.5052" x2="2.0066" y2="3.5052" width="0.1524" layer="39"/>
<wire x1="2.0066" y1="3.5052" x2="2.0066" y2="-3.5052" width="0.1524" layer="39"/>
<wire x1="-14.2494" y1="-3.2512" x2="1.7526" y2="-3.2512" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="-3.2512" x2="1.7526" y2="3.2512" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="3.2512" x2="-14.2494" y2="3.2512" width="0.1524" layer="21"/>
<wire x1="-14.2494" y1="3.2512" x2="-14.2494" y2="-3.2512" width="0.1524" layer="21"/>
<wire x1="-14.2494" y1="-3.2512" x2="1.7526" y2="-3.2512" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="-3.2512" x2="1.7526" y2="3.2512" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="3.2512" x2="-14.2494" y2="3.2512" width="0.1524" layer="51"/>
<wire x1="-14.2494" y1="3.2512" x2="-14.2494" y2="-3.2512" width="0.1524" layer="51"/>
<text x="-10.3886" y="5.3086" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-11.8872" y="-7.1628" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1500X800X1550">
<pad name="1" x="-12.4968" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="2.0066" y1="-4.4958" x2="-14.5034" y2="-4.4958" width="0.1524" layer="39"/>
<wire x1="-14.5034" y1="-4.4958" x2="-14.5034" y2="4.4958" width="0.1524" layer="39"/>
<wire x1="-14.5034" y1="4.4958" x2="2.0066" y2="4.4958" width="0.1524" layer="39"/>
<wire x1="2.0066" y1="4.4958" x2="2.0066" y2="-4.4958" width="0.1524" layer="39"/>
<wire x1="-14.2494" y1="-4.2418" x2="1.7526" y2="-4.2418" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="-4.2418" x2="1.7526" y2="4.2418" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="4.2418" x2="-14.2494" y2="4.2418" width="0.1524" layer="21"/>
<wire x1="-14.2494" y1="4.2418" x2="-14.2494" y2="-4.2418" width="0.1524" layer="21"/>
<wire x1="-14.2494" y1="-4.2418" x2="1.7526" y2="-4.2418" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="-4.2418" x2="1.7526" y2="4.2418" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="4.2418" x2="-14.2494" y2="4.2418" width="0.1524" layer="51"/>
<wire x1="-14.2494" y1="4.2418" x2="-14.2494" y2="-4.2418" width="0.1524" layer="51"/>
<text x="-10.8204" y="6.9088" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-11.938" y="-8.4328" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X450X1200">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-2.7432" x2="-16.764" y2="-2.7432" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-2.7432" x2="-16.764" y2="2.7432" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="2.7432" x2="1.7526" y2="2.7432" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="2.7432" x2="1.7526" y2="-2.7432" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-2.4892" x2="1.4986" y2="-2.4892" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-2.4892" x2="1.4986" y2="2.4892" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="2.4892" x2="-16.51" y2="2.4892" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="2.4892" x2="-16.51" y2="-2.4892" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-2.4892" x2="1.4986" y2="-2.4892" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-2.4892" x2="1.4986" y2="2.4892" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="2.4892" x2="-16.51" y2="2.4892" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="2.4892" x2="-16.51" y2="-2.4892" width="0.1524" layer="51"/>
<text x="-11.9126" y="4.7498" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-12.9794" y="-6.7056" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X500X1250">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-2.9972" x2="-16.764" y2="-2.9972" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-2.9972" x2="-16.764" y2="2.9972" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="2.9972" x2="1.7526" y2="2.9972" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="2.9972" x2="1.7526" y2="-2.9972" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-2.7432" x2="1.4986" y2="-2.7432" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-2.7432" x2="1.4986" y2="2.7432" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="2.7432" x2="-16.51" y2="2.7432" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="2.7432" x2="-16.51" y2="-2.7432" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-2.7432" x2="1.4986" y2="-2.7432" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-2.7432" x2="1.4986" y2="2.7432" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="2.7432" x2="-16.51" y2="2.7432" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="2.7432" x2="-16.51" y2="-2.7432" width="0.1524" layer="51"/>
<text x="-11.8618" y="6.0706" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-13.1826" y="-7.2644" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X550X1250">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-3.2512" x2="-16.764" y2="-3.2512" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-3.2512" x2="-16.764" y2="3.2512" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="3.2512" x2="1.7526" y2="3.2512" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="3.2512" x2="1.7526" y2="-3.2512" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-2.9972" x2="1.4986" y2="-2.9972" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-2.9972" x2="1.4986" y2="2.9972" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="2.9972" x2="-16.51" y2="2.9972" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="2.9972" x2="-16.51" y2="-2.9972" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-2.9972" x2="1.4986" y2="-2.9972" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-2.9972" x2="1.4986" y2="2.9972" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="2.9972" x2="-16.51" y2="2.9972" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="2.9972" x2="-16.51" y2="-2.9972" width="0.1524" layer="51"/>
<text x="-12.2174" y="6.4262" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-13.1064" y="-7.6708" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X600X1350">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-3.5052" x2="-16.764" y2="-3.5052" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-3.5052" x2="-16.764" y2="3.5052" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="3.5052" x2="1.7526" y2="3.5052" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="3.5052" x2="1.7526" y2="-3.5052" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-3.2512" x2="1.4986" y2="-3.2512" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-3.2512" x2="1.4986" y2="3.2512" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="3.2512" x2="-16.51" y2="3.2512" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="3.2512" x2="-16.51" y2="-3.2512" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-3.2512" x2="1.4986" y2="-3.2512" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-3.2512" x2="1.4986" y2="3.2512" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="3.2512" x2="-16.51" y2="3.2512" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="3.2512" x2="-16.51" y2="-3.2512" width="0.1524" layer="51"/>
<text x="-12.065" y="6.1976" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-13.1572" y="-8.0264" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X650X1500">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-3.7592" x2="-16.764" y2="-3.7592" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-3.7592" x2="-16.764" y2="3.7592" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="3.7592" x2="1.7526" y2="3.7592" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="3.7592" x2="1.7526" y2="-3.7592" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-3.5052" x2="1.4986" y2="-3.5052" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-3.5052" x2="1.4986" y2="3.5052" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="3.5052" x2="-16.51" y2="3.5052" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="3.5052" x2="-16.51" y2="-3.5052" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-3.5052" x2="1.4986" y2="-3.5052" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-3.5052" x2="1.4986" y2="3.5052" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="3.5052" x2="-16.51" y2="3.5052" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="3.5052" x2="-16.51" y2="-3.5052" width="0.1524" layer="51"/>
<text x="-11.8618" y="6.6802" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-12.954" y="-7.7978" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X750X1450">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-4.2418" x2="-16.764" y2="-4.2418" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-4.2418" x2="-16.764" y2="4.2418" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="4.2418" x2="1.7526" y2="4.2418" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="4.2418" x2="1.7526" y2="-4.2418" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-3.9878" x2="1.4986" y2="-3.9878" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-3.9878" x2="1.4986" y2="3.9878" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="3.9878" x2="-16.51" y2="3.9878" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="3.9878" x2="-16.51" y2="-3.9878" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-3.9878" x2="1.4986" y2="-3.9878" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-3.9878" x2="1.4986" y2="3.9878" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="3.9878" x2="-16.51" y2="3.9878" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="3.9878" x2="-16.51" y2="-3.9878" width="0.1524" layer="51"/>
<text x="-12.2428" y="6.3754" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-12.9032" y="-8.1534" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X800X1650">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-4.4958" x2="-16.764" y2="-4.4958" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-4.4958" x2="-16.764" y2="4.4958" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="4.4958" x2="1.7526" y2="4.4958" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="4.4958" x2="1.7526" y2="-4.4958" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-4.2418" x2="1.4986" y2="-4.2418" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-4.2418" x2="1.4986" y2="4.2418" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="4.2418" x2="-16.51" y2="4.2418" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="4.2418" x2="-16.51" y2="-4.2418" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-4.2418" x2="1.4986" y2="-4.2418" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-4.2418" x2="1.4986" y2="4.2418" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="4.2418" x2="-16.51" y2="4.2418" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="4.2418" x2="-16.51" y2="-4.2418" width="0.1524" layer="51"/>
<text x="-11.7602" y="7.7216" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-13.5636" y="-8.4836" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X900X1650">
<pad name="1" x="-15.0114" y="0" drill="0.8636" shape="square"/>
<pad name="2" x="0" y="0" drill="0.8636" rot="R180"/>
<wire x1="1.7526" y1="-5.0038" x2="-16.764" y2="-5.0038" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-5.0038" x2="-16.764" y2="5.0038" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="5.0038" x2="1.7526" y2="5.0038" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="5.0038" x2="1.7526" y2="-5.0038" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-4.7498" x2="1.4986" y2="-4.7498" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-4.7498" x2="1.4986" y2="4.7498" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="4.7498" x2="-16.51" y2="4.7498" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="4.7498" x2="-16.51" y2="-4.7498" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-4.7498" x2="1.4986" y2="-4.7498" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-4.7498" x2="1.4986" y2="4.7498" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="4.7498" x2="-16.51" y2="4.7498" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="4.7498" x2="-16.51" y2="-4.7498" width="0.1524" layer="51"/>
<text x="-12.1666" y="8.001" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-12.6746" y="-8.7884" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1750X950X1800">
<pad name="1" x="-15.0114" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="1.7526" y1="-5.2578" x2="-16.764" y2="-5.2578" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="-5.2578" x2="-16.764" y2="5.2578" width="0.1524" layer="39"/>
<wire x1="-16.764" y1="5.2578" x2="1.7526" y2="5.2578" width="0.1524" layer="39"/>
<wire x1="1.7526" y1="5.2578" x2="1.7526" y2="-5.2578" width="0.1524" layer="39"/>
<wire x1="-16.51" y1="-5.0038" x2="1.4986" y2="-5.0038" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="-5.0038" x2="1.4986" y2="5.0038" width="0.1524" layer="21"/>
<wire x1="1.4986" y1="5.0038" x2="-16.51" y2="5.0038" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="5.0038" x2="-16.51" y2="-5.0038" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-5.0038" x2="1.4986" y2="-5.0038" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="-5.0038" x2="1.4986" y2="5.0038" width="0.1524" layer="51"/>
<wire x1="1.4986" y1="5.0038" x2="-16.51" y2="5.0038" width="0.1524" layer="51"/>
<wire x1="-16.51" y1="5.0038" x2="-16.51" y2="-5.0038" width="0.1524" layer="51"/>
<text x="-12.065" y="8.2296" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-13.0556" y="-9.2964" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1800X800X1700">
<pad name="1" x="-15.0114" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-4.4958" x2="-17.2466" y2="-4.4958" width="0.1524" layer="39"/>
<wire x1="-17.2466" y1="-4.4958" x2="-17.2466" y2="4.4958" width="0.1524" layer="39"/>
<wire x1="-17.2466" y1="4.4958" x2="2.2606" y2="4.4958" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="4.4958" x2="2.2606" y2="-4.4958" width="0.1524" layer="39"/>
<wire x1="-16.9926" y1="-4.2418" x2="2.0066" y2="-4.2418" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-4.2418" x2="2.0066" y2="4.2418" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="4.2418" x2="-16.9926" y2="4.2418" width="0.1524" layer="21"/>
<wire x1="-16.9926" y1="4.2418" x2="-16.9926" y2="-4.2418" width="0.1524" layer="21"/>
<wire x1="-16.9926" y1="-4.2418" x2="2.0066" y2="-4.2418" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-4.2418" x2="2.0066" y2="4.2418" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="4.2418" x2="-16.9926" y2="4.2418" width="0.1524" layer="51"/>
<wire x1="-16.9926" y1="4.2418" x2="-16.9926" y2="-4.2418" width="0.1524" layer="51"/>
<text x="-12.4206" y="6.6294" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-13.0556" y="-8.763" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1800X900X1800">
<pad name="1" x="-15.0114" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-5.0038" x2="-17.2466" y2="-5.0038" width="0.1524" layer="39"/>
<wire x1="-17.2466" y1="-5.0038" x2="-17.2466" y2="5.0038" width="0.1524" layer="39"/>
<wire x1="-17.2466" y1="5.0038" x2="2.2606" y2="5.0038" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="5.0038" x2="2.2606" y2="-5.0038" width="0.1524" layer="39"/>
<wire x1="-16.9926" y1="-4.7498" x2="2.0066" y2="-4.7498" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-4.7498" x2="2.0066" y2="4.7498" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="4.7498" x2="-16.9926" y2="4.7498" width="0.1524" layer="21"/>
<wire x1="-16.9926" y1="4.7498" x2="-16.9926" y2="-4.7498" width="0.1524" layer="21"/>
<wire x1="-16.9926" y1="-4.7498" x2="2.0066" y2="-4.7498" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-4.7498" x2="2.0066" y2="4.7498" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="4.7498" x2="-16.9926" y2="4.7498" width="0.1524" layer="51"/>
<wire x1="-16.9926" y1="4.7498" x2="-16.9926" y2="-4.7498" width="0.1524" layer="51"/>
<text x="-12.1412" y="7.1882" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-13.3096" y="-9.144" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2550X1050X2000">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.0066" y1="-5.7658" x2="-24.511" y2="-5.7658" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="-5.7658" x2="-24.511" y2="5.7658" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="5.7658" x2="2.0066" y2="5.7658" width="0.1524" layer="39"/>
<wire x1="2.0066" y1="5.7658" x2="2.0066" y2="-5.7658" width="0.1524" layer="39"/>
<wire x1="-24.257" y1="-5.5118" x2="1.7526" y2="-5.5118" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="-5.5118" x2="1.7526" y2="5.5118" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="5.5118" x2="-24.257" y2="5.5118" width="0.1524" layer="21"/>
<wire x1="-24.257" y1="5.5118" x2="-24.257" y2="-5.5118" width="0.1524" layer="21"/>
<wire x1="-24.257" y1="-5.5118" x2="1.7526" y2="-5.5118" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="-5.5118" x2="1.7526" y2="5.5118" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="5.5118" x2="-24.257" y2="5.5118" width="0.1524" layer="51"/>
<wire x1="-24.257" y1="5.5118" x2="-24.257" y2="-5.5118" width="0.1524" layer="51"/>
<text x="-16.1798" y="9.6012" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-17.2466" y="-10.1092" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2550X1200X2200">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.0066" y1="-6.5024" x2="-24.511" y2="-6.5024" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="-6.5024" x2="-24.511" y2="6.5024" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="6.5024" x2="2.0066" y2="6.5024" width="0.1524" layer="39"/>
<wire x1="2.0066" y1="6.5024" x2="2.0066" y2="-6.5024" width="0.1524" layer="39"/>
<wire x1="-24.257" y1="-6.2484" x2="1.7526" y2="-6.2484" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="-6.2484" x2="1.7526" y2="6.2484" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="6.2484" x2="-24.257" y2="6.2484" width="0.1524" layer="21"/>
<wire x1="-24.257" y1="6.2484" x2="-24.257" y2="-6.2484" width="0.1524" layer="21"/>
<wire x1="-24.257" y1="-6.2484" x2="1.7526" y2="-6.2484" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="-6.2484" x2="1.7526" y2="6.2484" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="6.2484" x2="-24.257" y2="6.2484" width="0.1524" layer="51"/>
<wire x1="-24.257" y1="6.2484" x2="-24.257" y2="-6.2484" width="0.1524" layer="51"/>
<text x="-16.1544" y="9.7028" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-17.018" y="-10.9982" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2550X850X1800">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.0066" y1="-4.7498" x2="-24.511" y2="-4.7498" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="-4.7498" x2="-24.511" y2="4.7498" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="4.7498" x2="2.0066" y2="4.7498" width="0.1524" layer="39"/>
<wire x1="2.0066" y1="4.7498" x2="2.0066" y2="-4.7498" width="0.1524" layer="39"/>
<wire x1="-24.257" y1="-4.4958" x2="1.7526" y2="-4.4958" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="-4.4958" x2="1.7526" y2="4.4958" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="4.4958" x2="-24.257" y2="4.4958" width="0.1524" layer="21"/>
<wire x1="-24.257" y1="4.4958" x2="-24.257" y2="-4.4958" width="0.1524" layer="21"/>
<wire x1="-24.257" y1="-4.4958" x2="1.7526" y2="-4.4958" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="-4.4958" x2="1.7526" y2="4.4958" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="4.4958" x2="-24.257" y2="4.4958" width="0.1524" layer="51"/>
<wire x1="-24.257" y1="4.4958" x2="-24.257" y2="-4.4958" width="0.1524" layer="51"/>
<text x="-15.6972" y="6.6548" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-16.6116" y="-8.6614" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2600X1000X1750">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-5.5118" x2="-24.765" y2="-5.5118" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="-5.5118" x2="-24.765" y2="5.5118" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="5.5118" x2="2.2606" y2="5.5118" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="5.5118" x2="2.2606" y2="-5.5118" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="-5.2578" x2="2.0066" y2="-5.2578" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-5.2578" x2="2.0066" y2="5.2578" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="5.2578" x2="-24.511" y2="5.2578" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="5.2578" x2="-24.511" y2="-5.2578" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="-5.2578" x2="2.0066" y2="-5.2578" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-5.2578" x2="2.0066" y2="5.2578" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="5.2578" x2="-24.511" y2="5.2578" width="0.1524" layer="51"/>
<wire x1="-24.511" y1="5.2578" x2="-24.511" y2="-5.2578" width="0.1524" layer="51"/>
<text x="-16.2052" y="8.0264" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-16.8402" y="-9.7536" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2600X1050X2050">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-5.7658" x2="-24.765" y2="-5.7658" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="-5.7658" x2="-24.765" y2="5.7658" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="5.7658" x2="2.2606" y2="5.7658" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="5.7658" x2="2.2606" y2="-5.7658" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="-5.5118" x2="2.0066" y2="-5.5118" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-5.5118" x2="2.0066" y2="5.5118" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="5.5118" x2="-24.511" y2="5.5118" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="5.5118" x2="-24.511" y2="-5.5118" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="-5.5118" x2="2.0066" y2="-5.5118" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-5.5118" x2="2.0066" y2="5.5118" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="5.5118" x2="-24.511" y2="5.5118" width="0.1524" layer="51"/>
<wire x1="-24.511" y1="5.5118" x2="-24.511" y2="-5.5118" width="0.1524" layer="51"/>
<text x="-16.1036" y="7.9756" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-17.1704" y="-10.287" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2600X1200X1950">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-6.5024" x2="-24.765" y2="-6.5024" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="-6.5024" x2="-24.765" y2="6.5024" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="6.5024" x2="2.2606" y2="6.5024" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="6.5024" x2="2.2606" y2="-6.5024" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="-6.2484" x2="2.0066" y2="-6.2484" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-6.2484" x2="2.0066" y2="6.2484" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="6.2484" x2="-24.511" y2="6.2484" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="6.2484" x2="-24.511" y2="-6.2484" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="-6.2484" x2="2.0066" y2="-6.2484" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-6.2484" x2="2.0066" y2="6.2484" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="6.2484" x2="-24.511" y2="6.2484" width="0.1524" layer="51"/>
<wire x1="-24.511" y1="6.2484" x2="-24.511" y2="-6.2484" width="0.1524" layer="51"/>
<text x="-16.4592" y="8.5852" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-16.764" y="-10.414" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2600X1250X2250">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.5146" y1="-6.7564" x2="-24.9936" y2="-6.7564" width="0.1524" layer="39"/>
<wire x1="-24.9936" y1="-6.7564" x2="-24.9936" y2="6.7564" width="0.1524" layer="39"/>
<wire x1="-24.9936" y1="6.7564" x2="2.5146" y2="6.7564" width="0.1524" layer="39"/>
<wire x1="2.5146" y1="6.7564" x2="2.5146" y2="-6.7564" width="0.1524" layer="39"/>
<wire x1="-24.7396" y1="-6.5024" x2="2.2606" y2="-6.5024" width="0.1524" layer="21"/>
<wire x1="2.2606" y1="-6.5024" x2="2.2606" y2="6.5024" width="0.1524" layer="21"/>
<wire x1="2.2606" y1="6.5024" x2="-24.7396" y2="6.5024" width="0.1524" layer="21"/>
<wire x1="-24.7396" y1="6.5024" x2="-24.7396" y2="-6.5024" width="0.1524" layer="21"/>
<wire x1="-24.7396" y1="-6.5024" x2="2.2606" y2="-6.5024" width="0.1524" layer="51"/>
<wire x1="2.2606" y1="-6.5024" x2="2.2606" y2="6.5024" width="0.1524" layer="51"/>
<wire x1="2.2606" y1="6.5024" x2="-24.7396" y2="6.5024" width="0.1524" layer="51"/>
<wire x1="-24.7396" y1="6.5024" x2="-24.7396" y2="-6.5024" width="0.1524" layer="51"/>
<text x="-16.002" y="10.3632" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-16.8402" y="-11.1506" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2600X850X1550">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-4.7498" x2="-24.765" y2="-4.7498" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="-4.7498" x2="-24.765" y2="4.7498" width="0.1524" layer="39"/>
<wire x1="-24.765" y1="4.7498" x2="2.2606" y2="4.7498" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="4.7498" x2="2.2606" y2="-4.7498" width="0.1524" layer="39"/>
<wire x1="-24.511" y1="-4.4958" x2="2.0066" y2="-4.4958" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-4.4958" x2="2.0066" y2="4.4958" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="4.4958" x2="-24.511" y2="4.4958" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="4.4958" x2="-24.511" y2="-4.4958" width="0.1524" layer="21"/>
<wire x1="-24.511" y1="-4.4958" x2="2.0066" y2="-4.4958" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-4.4958" x2="2.0066" y2="4.4958" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="4.4958" x2="-24.511" y2="4.4958" width="0.1524" layer="51"/>
<wire x1="-24.511" y1="4.4958" x2="-24.511" y2="-4.4958" width="0.1524" layer="51"/>
<text x="-15.9258" y="7.0358" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-16.6624" y="-9.2456" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2600X900X1900">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.5146" y1="-5.0038" x2="-24.9936" y2="-5.0038" width="0.1524" layer="39"/>
<wire x1="-24.9936" y1="-5.0038" x2="-24.9936" y2="5.0038" width="0.1524" layer="39"/>
<wire x1="-24.9936" y1="5.0038" x2="2.5146" y2="5.0038" width="0.1524" layer="39"/>
<wire x1="2.5146" y1="5.0038" x2="2.5146" y2="-5.0038" width="0.1524" layer="39"/>
<wire x1="-24.7396" y1="-4.7498" x2="2.2606" y2="-4.7498" width="0.1524" layer="21"/>
<wire x1="2.2606" y1="-4.7498" x2="2.2606" y2="4.7498" width="0.1524" layer="21"/>
<wire x1="2.2606" y1="4.7498" x2="-24.7396" y2="4.7498" width="0.1524" layer="21"/>
<wire x1="-24.7396" y1="4.7498" x2="-24.7396" y2="-4.7498" width="0.1524" layer="21"/>
<wire x1="-24.7396" y1="-4.7498" x2="2.2606" y2="-4.7498" width="0.1524" layer="51"/>
<wire x1="2.2606" y1="-4.7498" x2="2.2606" y2="4.7498" width="0.1524" layer="51"/>
<wire x1="2.2606" y1="4.7498" x2="-24.7396" y2="4.7498" width="0.1524" layer="51"/>
<wire x1="-24.7396" y1="4.7498" x2="-24.7396" y2="-4.7498" width="0.1524" layer="51"/>
<text x="-15.9004" y="7.62" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-16.891" y="-8.9662" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM2700X1650X2600">
<pad name="1" x="-22.5044" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.9972" y1="-8.763" x2="-25.5016" y2="-8.763" width="0.1524" layer="39"/>
<wire x1="-25.5016" y1="-8.763" x2="-25.5016" y2="8.763" width="0.1524" layer="39"/>
<wire x1="-25.5016" y1="8.763" x2="2.9972" y2="8.763" width="0.1524" layer="39"/>
<wire x1="2.9972" y1="8.763" x2="2.9972" y2="-8.763" width="0.1524" layer="39"/>
<wire x1="-25.2476" y1="-8.509" x2="2.7432" y2="-8.509" width="0.1524" layer="21"/>
<wire x1="2.7432" y1="-8.509" x2="2.7432" y2="8.509" width="0.1524" layer="21"/>
<wire x1="2.7432" y1="8.509" x2="-25.2476" y2="8.509" width="0.1524" layer="21"/>
<wire x1="-25.2476" y1="8.509" x2="-25.2476" y2="-8.509" width="0.1524" layer="21"/>
<wire x1="-25.2476" y1="-8.509" x2="2.7432" y2="-8.509" width="0.1524" layer="51"/>
<wire x1="2.7432" y1="-8.509" x2="2.7432" y2="8.509" width="0.1524" layer="51"/>
<wire x1="2.7432" y1="8.509" x2="-25.2476" y2="8.509" width="0.1524" layer="51"/>
<wire x1="-25.2476" y1="8.509" x2="-25.2476" y2="-8.509" width="0.1524" layer="51"/>
<text x="-16.4084" y="10.9728" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-17.2212" y="-12.9794" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM3050X1650X2650">
<pad name="1" x="-27.5082" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.0066" y1="-8.763" x2="-29.5148" y2="-8.763" width="0.1524" layer="39"/>
<wire x1="-29.5148" y1="-8.763" x2="-29.5148" y2="8.763" width="0.1524" layer="39"/>
<wire x1="-29.5148" y1="8.763" x2="2.0066" y2="8.763" width="0.1524" layer="39"/>
<wire x1="2.0066" y1="8.763" x2="2.0066" y2="-8.763" width="0.1524" layer="39"/>
<wire x1="-29.2608" y1="-8.509" x2="1.7526" y2="-8.509" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="-8.509" x2="1.7526" y2="8.509" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="8.509" x2="-29.2608" y2="8.509" width="0.1524" layer="21"/>
<wire x1="-29.2608" y1="8.509" x2="-29.2608" y2="-8.509" width="0.1524" layer="21"/>
<wire x1="-29.2608" y1="-8.509" x2="1.7526" y2="-8.509" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="-8.509" x2="1.7526" y2="8.509" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="8.509" x2="-29.2608" y2="8.509" width="0.1524" layer="51"/>
<wire x1="-29.2608" y1="8.509" x2="-29.2608" y2="-8.509" width="0.1524" layer="51"/>
<text x="-18.7706" y="12.2428" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-19.7612" y="-12.9794" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM3050X1900X3000">
<pad name="1" x="-27.5082" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.0066" y1="-10.0076" x2="-29.5148" y2="-10.0076" width="0.1524" layer="39"/>
<wire x1="-29.5148" y1="-10.0076" x2="-29.5148" y2="10.0076" width="0.1524" layer="39"/>
<wire x1="-29.5148" y1="10.0076" x2="2.0066" y2="10.0076" width="0.1524" layer="39"/>
<wire x1="2.0066" y1="10.0076" x2="2.0066" y2="-10.0076" width="0.1524" layer="39"/>
<wire x1="-29.2608" y1="-9.7536" x2="1.7526" y2="-9.7536" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="-9.7536" x2="1.7526" y2="9.7536" width="0.1524" layer="21"/>
<wire x1="1.7526" y1="9.7536" x2="-29.2608" y2="9.7536" width="0.1524" layer="21"/>
<wire x1="-29.2608" y1="9.7536" x2="-29.2608" y2="-9.7536" width="0.1524" layer="21"/>
<wire x1="-29.2608" y1="-9.7536" x2="1.7526" y2="-9.7536" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="-9.7536" x2="1.7526" y2="9.7536" width="0.1524" layer="51"/>
<wire x1="1.7526" y1="9.7536" x2="-29.2608" y2="9.7536" width="0.1524" layer="51"/>
<wire x1="-29.2608" y1="9.7536" x2="-29.2608" y2="-9.7536" width="0.1524" layer="51"/>
<text x="-18.7452" y="12.7762" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-19.304" y="-14.097" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM3100X1200X2250">
<pad name="1" x="-27.5082" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-6.5024" x2="-29.7434" y2="-6.5024" width="0.1524" layer="39"/>
<wire x1="-29.7434" y1="-6.5024" x2="-29.7434" y2="6.5024" width="0.1524" layer="39"/>
<wire x1="-29.7434" y1="6.5024" x2="2.2606" y2="6.5024" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="6.5024" x2="2.2606" y2="-6.5024" width="0.1524" layer="39"/>
<wire x1="-29.4894" y1="-6.2484" x2="2.0066" y2="-6.2484" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-6.2484" x2="2.0066" y2="6.2484" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="6.2484" x2="-29.4894" y2="6.2484" width="0.1524" layer="21"/>
<wire x1="-29.4894" y1="6.2484" x2="-29.4894" y2="-6.2484" width="0.1524" layer="21"/>
<wire x1="-29.4894" y1="-6.2484" x2="2.0066" y2="-6.2484" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-6.2484" x2="2.0066" y2="6.2484" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="6.2484" x2="-29.4894" y2="6.2484" width="0.1524" layer="51"/>
<wire x1="-29.4894" y1="6.2484" x2="-29.4894" y2="-6.2484" width="0.1524" layer="51"/>
<text x="-19.0246" y="8.9662" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-19.177" y="-10.4648" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM3100X1450X2500">
<pad name="1" x="-27.5082" y="0" drill="1.0414" shape="square"/>
<pad name="2" x="0" y="0" drill="1.0414" rot="R180"/>
<wire x1="2.2606" y1="-7.747" x2="-29.7434" y2="-7.747" width="0.1524" layer="39"/>
<wire x1="-29.7434" y1="-7.747" x2="-29.7434" y2="7.747" width="0.1524" layer="39"/>
<wire x1="-29.7434" y1="7.747" x2="2.2606" y2="7.747" width="0.1524" layer="39"/>
<wire x1="2.2606" y1="7.747" x2="2.2606" y2="-7.747" width="0.1524" layer="39"/>
<wire x1="-29.4894" y1="-7.493" x2="2.0066" y2="-7.493" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="-7.493" x2="2.0066" y2="7.493" width="0.1524" layer="21"/>
<wire x1="2.0066" y1="7.493" x2="-29.4894" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-29.4894" y1="7.493" x2="-29.4894" y2="-7.493" width="0.1524" layer="21"/>
<wire x1="-29.4894" y1="-7.493" x2="2.0066" y2="-7.493" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="-7.493" x2="2.0066" y2="7.493" width="0.1524" layer="51"/>
<wire x1="2.0066" y1="7.493" x2="-29.4894" y2="7.493" width="0.1524" layer="51"/>
<wire x1="-29.4894" y1="7.493" x2="-29.4894" y2="-7.493" width="0.1524" layer="51"/>
<text x="-18.3388" y="10.033" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-19.431" y="-11.5824" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM1020X400X1000">
<pad name="1" x="-7.493" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<wire x1="1.6002" y1="-2.2606" x2="-9.0932" y2="-2.2606" width="0.1524" layer="39"/>
<wire x1="-9.0932" y1="-2.2606" x2="-9.0932" y2="2.2606" width="0.1524" layer="39"/>
<wire x1="-9.0932" y1="2.2606" x2="1.6002" y2="2.2606" width="0.1524" layer="39"/>
<wire x1="1.6002" y1="2.2606" x2="1.6002" y2="-2.2606" width="0.1524" layer="39"/>
<wire x1="-8.8392" y1="-2.0066" x2="1.3462" y2="-2.0066" width="0.1524" layer="21"/>
<wire x1="1.3462" y1="-2.0066" x2="1.3462" y2="2.0066" width="0.1524" layer="21"/>
<wire x1="1.3462" y1="2.0066" x2="-8.8392" y2="2.0066" width="0.1524" layer="21"/>
<wire x1="-8.8392" y1="2.0066" x2="-8.8392" y2="-2.0066" width="0.1524" layer="21"/>
<wire x1="-8.8392" y1="-2.0066" x2="1.3462" y2="-2.0066" width="0.1524" layer="51"/>
<wire x1="1.3462" y1="-2.0066" x2="1.3462" y2="2.0066" width="0.1524" layer="51"/>
<wire x1="1.3462" y1="2.0066" x2="-8.8392" y2="2.0066" width="0.1524" layer="51"/>
<wire x1="-8.8392" y1="2.0066" x2="-8.8392" y2="-2.0066" width="0.1524" layer="51"/>
<text x="-8.5852" y="4.7498" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-9.4742" y="-6.4008" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM750X450X800">
<pad name="1" x="-5.0038" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<text x="-7.0358" y="5.2324" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-7.9756" y="-6.7818" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
<wire x1="1.4986" y1="-2.5146" x2="-6.5024" y2="-2.5146" width="0.1524" layer="39"/>
<wire x1="-6.5024" y1="-2.5146" x2="-6.5024" y2="2.5146" width="0.1524" layer="39"/>
<wire x1="-6.5024" y1="2.5146" x2="1.4986" y2="2.5146" width="0.1524" layer="39"/>
<wire x1="1.4986" y1="2.5146" x2="1.4986" y2="-2.5146" width="0.1524" layer="39"/>
<wire x1="-6.2484" y1="-2.2606" x2="1.2446" y2="-2.2606" width="0.1524" layer="21"/>
<wire x1="1.2446" y1="-2.2606" x2="1.2446" y2="2.2606" width="0.1524" layer="21"/>
<wire x1="1.2446" y1="2.2606" x2="-6.2484" y2="2.2606" width="0.1524" layer="21"/>
<wire x1="-6.2484" y1="2.2606" x2="-6.2484" y2="-2.2606" width="0.1524" layer="21"/>
<wire x1="-6.2484" y1="-2.2606" x2="1.2446" y2="-2.2606" width="0.1524" layer="51"/>
<wire x1="1.2446" y1="-2.2606" x2="1.2446" y2="2.2606" width="0.1524" layer="51"/>
<wire x1="1.2446" y1="2.2606" x2="-6.2484" y2="2.2606" width="0.1524" layer="51"/>
<wire x1="-6.2484" y1="2.2606" x2="-6.2484" y2="-2.2606" width="0.1524" layer="51"/>
<text x="-7.0358" y="5.2324" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-7.9756" y="-6.7818" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM730X400X600">
<pad name="1" x="-5.0038" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<wire x1="1.397" y1="-2.2606" x2="-6.4008" y2="-2.2606" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="-2.2606" x2="-6.4008" y2="2.2606" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="2.2606" x2="1.397" y2="2.2606" width="0.1524" layer="39"/>
<wire x1="1.397" y1="2.2606" x2="1.397" y2="-2.2606" width="0.1524" layer="39"/>
<wire x1="-6.1468" y1="-2.0066" x2="1.143" y2="-2.0066" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-2.0066" x2="1.143" y2="2.0066" width="0.1524" layer="21"/>
<wire x1="1.143" y1="2.0066" x2="-6.1468" y2="2.0066" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="2.0066" x2="-6.1468" y2="-2.0066" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="-2.0066" x2="1.143" y2="-2.0066" width="0.1524" layer="51"/>
<wire x1="1.143" y1="-2.0066" x2="1.143" y2="2.0066" width="0.1524" layer="51"/>
<wire x1="1.143" y1="2.0066" x2="-6.1468" y2="2.0066" width="0.1524" layer="51"/>
<wire x1="-6.1468" y1="2.0066" x2="-6.1468" y2="-2.0066" width="0.1524" layer="51"/>
<text x="-6.9596" y="5.0038" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-8.1026" y="-6.731" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM730X400X900">
<pad name="1" x="-5.0038" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<wire x1="1.397" y1="-2.2606" x2="-6.4008" y2="-2.2606" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="-2.2606" x2="-6.4008" y2="2.2606" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="2.2606" x2="1.397" y2="2.2606" width="0.1524" layer="39"/>
<wire x1="1.397" y1="2.2606" x2="1.397" y2="-2.2606" width="0.1524" layer="39"/>
<wire x1="-6.1468" y1="-2.0066" x2="1.143" y2="-2.0066" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-2.0066" x2="1.143" y2="2.0066" width="0.1524" layer="21"/>
<wire x1="1.143" y1="2.0066" x2="-6.1468" y2="2.0066" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="2.0066" x2="-6.1468" y2="-2.0066" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="-2.0066" x2="1.143" y2="-2.0066" width="0.1524" layer="51"/>
<wire x1="1.143" y1="-2.0066" x2="1.143" y2="2.0066" width="0.1524" layer="51"/>
<wire x1="1.143" y1="2.0066" x2="-6.1468" y2="2.0066" width="0.1524" layer="51"/>
<wire x1="-6.1468" y1="2.0066" x2="-6.1468" y2="-2.0066" width="0.1524" layer="51"/>
<text x="-7.3406" y="4.9784" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-8.1026" y="-6.2484" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM730X480X650">
<pad name="1" x="-5.0038" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<wire x1="1.397" y1="-2.6416" x2="-6.4008" y2="-2.6416" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="-2.6416" x2="-6.4008" y2="2.6416" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="2.6416" x2="1.397" y2="2.6416" width="0.1524" layer="39"/>
<wire x1="1.397" y1="2.6416" x2="1.397" y2="-2.6416" width="0.1524" layer="39"/>
<wire x1="-6.1468" y1="-2.3876" x2="1.143" y2="-2.3876" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-2.3876" x2="1.143" y2="2.3876" width="0.1524" layer="21"/>
<wire x1="1.143" y1="2.3876" x2="-6.1468" y2="2.3876" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="2.3876" x2="-6.1468" y2="-2.3876" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="-2.3876" x2="1.143" y2="-2.3876" width="0.1524" layer="51"/>
<wire x1="1.143" y1="-2.3876" x2="1.143" y2="2.3876" width="0.1524" layer="51"/>
<wire x1="1.143" y1="2.3876" x2="-6.1468" y2="2.3876" width="0.1524" layer="51"/>
<wire x1="-6.1468" y1="2.3876" x2="-6.1468" y2="-2.3876" width="0.1524" layer="51"/>
<text x="-7.2644" y="4.826" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-8.128" y="-6.2738" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM730X320X600">
<pad name="1" x="-5.0038" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<text x="-7.1882" y="3.8354" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-8.128" y="-6.2484" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
<wire x1="1.397" y1="-1.8542" x2="-6.4008" y2="-1.8542" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="-1.8542" x2="-6.4008" y2="1.8542" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="1.8542" x2="1.397" y2="1.8542" width="0.1524" layer="39"/>
<wire x1="1.397" y1="1.8542" x2="1.397" y2="-1.8542" width="0.1524" layer="39"/>
<wire x1="-6.1468" y1="-1.6002" x2="1.143" y2="-1.6002" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-1.6002" x2="1.143" y2="1.6002" width="0.1524" layer="21"/>
<wire x1="1.143" y1="1.6002" x2="-6.1468" y2="1.6002" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="1.6002" x2="-6.1468" y2="-1.6002" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="-1.6002" x2="1.143" y2="-1.6002" width="0.1524" layer="51"/>
<wire x1="1.143" y1="-1.6002" x2="1.143" y2="1.6002" width="0.1524" layer="51"/>
<wire x1="1.143" y1="1.6002" x2="-6.1468" y2="1.6002" width="0.1524" layer="51"/>
<wire x1="-6.1468" y1="1.6002" x2="-6.1468" y2="-1.6002" width="0.1524" layer="51"/>
<text x="-7.1882" y="3.8354" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-8.128" y="-6.2484" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM730X600X830">
<pad name="1" x="-5.0038" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<wire x1="1.397" y1="-3.2512" x2="-6.4008" y2="-3.2512" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="-3.2512" x2="-6.4008" y2="3.2512" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="3.2512" x2="1.397" y2="3.2512" width="0.1524" layer="39"/>
<wire x1="1.397" y1="3.2512" x2="1.397" y2="-3.2512" width="0.1524" layer="39"/>
<wire x1="-6.1468" y1="-2.9972" x2="1.143" y2="-2.9972" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-2.9972" x2="1.143" y2="2.9972" width="0.1524" layer="21"/>
<wire x1="1.143" y1="2.9972" x2="-6.1468" y2="2.9972" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="2.9972" x2="-6.1468" y2="-2.9972" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="-2.9972" x2="1.143" y2="-2.9972" width="0.1524" layer="51"/>
<wire x1="1.143" y1="-2.9972" x2="1.143" y2="2.9972" width="0.1524" layer="51"/>
<wire x1="1.143" y1="2.9972" x2="-6.1468" y2="2.9972" width="0.1524" layer="51"/>
<wire x1="-6.1468" y1="2.9972" x2="-6.1468" y2="-2.9972" width="0.1524" layer="51"/>
<text x="-6.985" y="6.0452" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-7.9756" y="-7.4676" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="CAPM730X600X1130">
<pad name="1" x="-5.0038" y="0" drill="0.762" shape="square"/>
<pad name="2" x="0" y="0" drill="0.762" rot="R180"/>
<wire x1="1.397" y1="-3.2512" x2="-6.4008" y2="-3.2512" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="-3.2512" x2="-6.4008" y2="3.2512" width="0.1524" layer="39"/>
<wire x1="-6.4008" y1="3.2512" x2="1.397" y2="3.2512" width="0.1524" layer="39"/>
<wire x1="1.397" y1="3.2512" x2="1.397" y2="-3.2512" width="0.1524" layer="39"/>
<wire x1="-6.1468" y1="-2.9972" x2="1.143" y2="-2.9972" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-2.9972" x2="1.143" y2="2.9972" width="0.1524" layer="21"/>
<wire x1="1.143" y1="2.9972" x2="-6.1468" y2="2.9972" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="2.9972" x2="-6.1468" y2="-2.9972" width="0.1524" layer="21"/>
<wire x1="-6.1468" y1="-2.9972" x2="1.143" y2="-2.9972" width="0.1524" layer="51"/>
<wire x1="1.143" y1="-2.9972" x2="1.143" y2="2.9972" width="0.1524" layer="51"/>
<wire x1="1.143" y1="2.9972" x2="-6.1468" y2="2.9972" width="0.1524" layer="51"/>
<wire x1="-6.1468" y1="2.9972" x2="-6.1468" y2="-2.9972" width="0.1524" layer="51"/>
<text x="-7.0104" y="6.1976" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-8.0518" y="-7.2898" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
<package name="TO126">
<description>&lt;b&gt;TO 126 horizontal&lt;/b&gt;</description>
<wire x1="-3.937" y1="-1.27" x2="-3.937" y2="9.144" width="0.127" layer="21"/>
<wire x1="-3.937" y1="9.144" x2="3.937" y2="9.144" width="0.127" layer="21"/>
<wire x1="3.937" y1="9.144" x2="3.937" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-3.937" y1="-1.27" x2="3.937" y2="-1.27" width="0.127" layer="21"/>
<wire x1="1.2393" y1="3.1591" x2="1.9493" y2="3.8858" width="0.127" layer="21" curve="25.6775"/>
<wire x1="0.7687" y1="3.6188" x2="1.2393" y2="3.1591" width="0.127" layer="21"/>
<wire x1="-0.7687" y1="3.6188" x2="-1.2393" y2="3.1591" width="0.127" layer="21"/>
<wire x1="-1.4787" y1="4.3456" x2="-1.9493" y2="3.8858" width="0.127" layer="21"/>
<wire x1="-1.9493" y1="3.8858" x2="-1.2393" y2="3.1591" width="0.127" layer="21" curve="25.6775"/>
<wire x1="0.508" y1="6.6509" x2="0.508" y2="7.3088" width="0.127" layer="21"/>
<wire x1="-0.508" y1="6.6509" x2="-0.508" y2="7.3088" width="0.127" layer="21"/>
<wire x1="-0.508" y1="7.3088" x2="0.508" y2="7.3088" width="0.127" layer="21" curve="-25.6796"/>
<wire x1="1.4787" y1="4.3456" x2="1.9493" y2="3.8858" width="0.127" layer="21"/>
<circle x="-3.1242" y="-0.4826" radius="0.4318" width="0" layer="21"/>
<circle x="0" y="5.08" radius="3.81" width="0" layer="42"/>
<circle x="0" y="5.08" radius="3.81" width="0" layer="43"/>
<circle x="0" y="5.08" radius="1.651" width="0.127" layer="21"/>
<pad name="1" x="-2.286" y="-5.08" drill="1.1176" shape="long" rot="R90"/>
<pad name="2" x="0" y="-5.08" drill="1.1176" shape="long" rot="R90"/>
<pad name="3" x="2.286" y="-5.08" drill="1.1176" shape="long" rot="R90"/>
<text x="-2.54" y="7.62" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.175" y="1.397" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-2.54" y="-0.889" size="1.27" layer="51" ratio="10">1</text>
<text x="-0.508" y="-0.889" size="1.27" layer="51" ratio="10">2</text>
<text x="1.778" y="-0.889" size="1.27" layer="51" ratio="10">3</text>
<rectangle x1="-0.635" y1="-3.048" x2="0.635" y2="-1.27" layer="21"/>
<rectangle x1="-2.667" y1="-3.429" x2="-1.905" y2="-1.27" layer="21"/>
<rectangle x1="-2.667" y1="-5.207" x2="-1.905" y2="-3.429" layer="51"/>
<rectangle x1="-0.381" y1="-3.429" x2="0.381" y2="-1.27" layer="21"/>
<rectangle x1="-0.381" y1="-5.207" x2="0.381" y2="-3.429" layer="51"/>
<rectangle x1="1.905" y1="-3.429" x2="2.667" y2="-1.27" layer="21"/>
<rectangle x1="1.905" y1="-5.207" x2="2.667" y2="-3.429" layer="51"/>
<hole x="0" y="5.08" drill="3.302"/>
</package>
<package name="EIA3216">
<wire x1="-1" y1="-1.2" x2="-2.5" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.2" x2="-2.5" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="-1.2" x2="2.5" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-0.8" x2="2.5" y2="0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.8" x2="2.1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<smd name="A" x="1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528">
<wire x1="-0.9" y1="-1.6" x2="-2.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-1.6" x2="-2.6" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.2" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-1.55" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="2.6" y2="1.25" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.25" x2="2.2" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.2032" layer="21" style="longdash"/>
<smd name="C" x="-1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<smd name="A" x="1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="CPOL-RADIAL-100UF-25V">
<wire x1="-0.635" y1="1.27" x2="-1.905" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="3.25" width="0.2032" layer="21"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="1.651" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-10UF-25V">
<wire x1="-0.762" y1="1.397" x2="-1.778" y2="1.397" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="2.5" width="0.2032" layer="21"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<text x="-0.889" y="1.524" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.905" y="-3.683" size="0.8128" layer="27">&gt;Value</text>
</package>
<package name="EIA7343">
<wire x1="-5" y1="2.5" x2="-2" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="2.5" x2="-5" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="-2.5" x2="-2" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="2" y1="2.5" x2="4" y2="2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="2.5" x2="5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="1.5" x2="5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="-1.5" x2="4" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="-2.5" x2="2" y2="-2.5" width="0.2032" layer="21"/>
<smd name="C" x="-3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<smd name="A" x="3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="-1.27" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="PANASONIC_G">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package G&lt;/b&gt;</description>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="-2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="1" x2="-5.1" y2="5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="1" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-1" x2="5.1" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="-1" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="-1" x2="4.85" y2="-1" width="0.2032" layer="21" curve="156.699401" cap="flat"/>
<wire x1="-4.85" y1="1" x2="4.85" y2="1" width="0.2032" layer="21" curve="-156.699401" cap="flat"/>
<wire x1="-3.25" y1="3.7" x2="-3.25" y2="-3.65" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="4.95" width="0.1016" layer="51"/>
<smd name="-" x="-4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<smd name="+" x="4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-5.85" y1="-0.45" x2="-4.9" y2="0.45" layer="51"/>
<rectangle x1="4.9" y1="-0.45" x2="5.85" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-3.3" y="3.6"/>
<vertex x="-4.05" y="2.75"/>
<vertex x="-4.65" y="1.55"/>
<vertex x="-4.85" y="0.45"/>
<vertex x="-4.85" y="-0.45"/>
<vertex x="-4.65" y="-1.55"/>
<vertex x="-4.05" y="-2.75"/>
<vertex x="-3.3" y="-3.6"/>
<vertex x="-3.3" y="3.55"/>
</polygon>
</package>
<package name="PANASONIC_E">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="-1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="0.9" x2="-4.1" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="0.9" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-0.9" x2="4.1" y2="-1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="-0.9" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="3.25" x2="-2.2" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.85" y1="0.9" x2="3.85" y2="0.9" width="0.2032" layer="21" curve="-153.684915" cap="flat"/>
<wire x1="-3.85" y1="-0.9" x2="3.85" y2="-0.9" width="0.2032" layer="21" curve="153.684915" cap="flat"/>
<circle x="0" y="0" radius="3.95" width="0.1016" layer="51"/>
<smd name="-" x="-3" y="0" dx="3.8" dy="1.4" layer="1"/>
<smd name="+" x="3" y="0" dx="3.8" dy="1.4" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-4.5" y1="-0.35" x2="-3.8" y2="0.35" layer="51"/>
<rectangle x1="3.8" y1="-0.35" x2="4.5" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.25" y="3.2"/>
<vertex x="-3" y="2.5"/>
<vertex x="-3.6" y="1.5"/>
<vertex x="-3.85" y="0.65"/>
<vertex x="-3.85" y="-0.65"/>
<vertex x="-3.55" y="-1.6"/>
<vertex x="-2.95" y="-2.55"/>
<vertex x="-2.25" y="-3.2"/>
<vertex x="-2.25" y="3.15"/>
</polygon>
</package>
<package name="PANASONIC_C">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.2032" layer="21"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.1016" layer="51"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.1016" layer="51"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="0.35" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-2.85" x2="-2.6" y2="-0.75" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="0.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="2.7" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="-1.75" width="0.1016" layer="51"/>
<wire x1="-2.4" y1="0.35" x2="2.45" y2="0.3" width="0.2032" layer="21" curve="-156.699401"/>
<wire x1="2.5" y1="-0.7" x2="-2.4" y2="-0.75" width="0.2032" layer="21" curve="-154.694887"/>
<circle x="0.05" y="-0.2" radius="2.5004" width="0.1016" layer="51"/>
<smd name="-" x="-1.8" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<smd name="+" x="1.9" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<text x="-2.6" y="2.7" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.6" y="-3.45" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="NIPPON_F80">
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.1016" layer="51"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="-3.3" x2="-3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="2" x2="3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="3.3" y1="2" x2="3.3" y2="-2" width="0.1016" layer="51"/>
<wire x1="-3.1" y1="0.685" x2="3.1" y2="0.685" width="0.2032" layer="21" curve="-156.500033"/>
<wire x1="3.1" y1="-0.685" x2="-3.1" y2="-0.685" width="0.2032" layer="21" curve="-154.748326"/>
<circle x="0" y="0" radius="3.15" width="0.1016" layer="51"/>
<smd name="-" x="-2.4" y="0" dx="2.95" dy="1" layer="1"/>
<smd name="+" x="2.4" y="0" dx="2.95" dy="1" layer="1"/>
<text x="-3.2" y="3.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.2" y="-3.85" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_D">
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="-1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="0.95" x2="-3.25" y2="3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="0.95" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-0.95" x2="3.25" y2="-1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="-0.95" width="0.1016" layer="21"/>
<wire x1="2.95" y1="0.95" x2="-2.95" y2="0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.95" y1="-0.95" x2="2.95" y2="-0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.1" y1="2.25" x2="-2.1" y2="-2.2" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="3.1" width="0.1016" layer="51"/>
<smd name="+" x="2.4" y="0" dx="3" dy="1.4" layer="1"/>
<smd name="-" x="-2.4" y="0" dx="3" dy="1.4" layer="1"/>
<text x="-1.75" y="1" size="1.016" layer="25">&gt;NAME</text>
<text x="-1.75" y="-1.975" size="1.016" layer="27">&gt;VALUE</text>
<rectangle x1="-3.65" y1="-0.35" x2="-3.05" y2="0.35" layer="51"/>
<rectangle x1="3.05" y1="-0.35" x2="3.65" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.15" y="2.15"/>
<vertex x="-2.6" y="1.6"/>
<vertex x="-2.9" y="0.9"/>
<vertex x="-3.05" y="0"/>
<vertex x="-2.9" y="-0.95"/>
<vertex x="-2.55" y="-1.65"/>
<vertex x="-2.15" y="-2.15"/>
<vertex x="-2.15" y="2.1"/>
</polygon>
</package>
<package name="CPOL-RADIAL-1000UF-63V">
<wire x1="-3.175" y1="1.905" x2="-4.445" y2="1.905" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="8.001" width="0.2032" layer="21"/>
<pad name="2" x="-3.81" y="0" drill="1.016" diameter="1.6764"/>
<pad name="1" x="3.81" y="0" drill="1.016" diameter="1.651" shape="square"/>
<text x="-2.54" y="8.89" size="0.8128" layer="27">&gt;Value</text>
<text x="-2.54" y="10.16" size="0.8128" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-1000UF-25V">
<wire x1="-1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="5.461" width="0.2032" layer="21"/>
<pad name="2" x="-2.54" y="0" drill="0.7" diameter="1.651"/>
<pad name="1" x="2.54" y="0" drill="0.7" diameter="1.651" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="2.921" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="VISHAY_C">
<wire x1="0" y1="1.27" x2="0" y2="1.905" width="0.254" layer="21"/>
<wire x1="-2.0574" y1="4.2926" x2="-2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="-2.0574" y1="-4.2926" x2="2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="-4.2926" x2="2.0574" y2="4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="4.2926" x2="-2.0574" y2="4.2926" width="0.127" layer="21"/>
<smd name="+" x="0" y="3.048" dx="3.556" dy="1.778" layer="1"/>
<smd name="-" x="0" y="-3.048" dx="3.556" dy="1.778" layer="1"/>
<text x="-1.905" y="4.445" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.905" y="-5.08" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_H13">
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="4" x2="6.75" y2="-4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="1" x2="-6.75" y2="6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="4" x2="6.75" y2="1" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-1" x2="6.75" y2="-4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="-1" width="0.2032" layer="21"/>
<wire x1="-6.55" y1="-1.2" x2="6.45" y2="-1.2" width="0.2032" layer="21" curve="156.692742" cap="flat"/>
<wire x1="-6.55" y1="1.2" x2="6.55" y2="1.2" width="0.2032" layer="21" curve="-156.697982" cap="flat"/>
<wire x1="-5" y1="4.25" x2="-4.95" y2="-4.35" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="6.6" width="0.1016" layer="51"/>
<smd name="-" x="-4.7" y="0" dx="5" dy="1.6" layer="1"/>
<smd name="+" x="4.7" y="0" dx="5" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-7.55" y1="-0.45" x2="-6.6" y2="0.45" layer="51"/>
<rectangle x1="6.6" y1="-0.45" x2="7.55" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-5" y="4.2"/>
<vertex x="-5.75" y="3.15"/>
<vertex x="-6.25" y="2.05"/>
<vertex x="-6.55" y="0.45"/>
<vertex x="-6.55" y="-0.45"/>
<vertex x="-6.35" y="-1.65"/>
<vertex x="-5.75" y="-3.25"/>
<vertex x="-5" y="-4.2"/>
</polygon>
</package>
<package name="EIA6032">
<wire x1="3.2" y1="-1.6" x2="3.2" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="3.2" y2="-1.6" width="0.127" layer="21"/>
<wire x1="3.2" y1="1.6" x2="-2.8" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="1.6" x2="-3.4" y2="1" width="0.127" layer="21"/>
<wire x1="-3.4" y1="1" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<smd name="P$1" x="-2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
<smd name="P$2" x="2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
</package>
<package name="EN_J2">
<description>Type J2 package for SMD supercap PRT-10317 (p# EEC-EN0F204J2)</description>
<wire x1="-2.5" y1="-3.5" x2="2.5" y2="-3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="2.1" y2="3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="-2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="-2.5" y1="3.1" x2="-2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="2.1" y1="3.5" x2="2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="2.5" y1="3.1" x2="2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="-2.5" y1="-3.5" x2="-2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="2.5" y1="-3.5" x2="2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="-2.5908" y1="-2.413" x2="-2.5654" y2="2.4384" width="0.127" layer="21" curve="-91.212564"/>
<wire x1="2.5908" y1="-2.413" x2="2.5654" y2="2.4384" width="0.127" layer="21" curve="86.79344"/>
<wire x1="1.7272" y1="-1.27" x2="1.7272" y2="-2.0828" width="0.127" layer="21"/>
<wire x1="1.3462" y1="-1.6764" x2="2.159" y2="-1.6764" width="0.127" layer="21"/>
<circle x="0" y="0" radius="3.4" width="0.127" layer="51"/>
<smd name="-" x="0" y="2.8" dx="5" dy="2.4" layer="1"/>
<smd name="+" x="0" y="-3.2" dx="5" dy="1.6" layer="1"/>
<text x="-2.28" y="0.66" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.31" y="-1.21" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528-KIT">
<description>&lt;h3&gt;EIA3528-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-0.9" y1="-1.6" x2="-3.1" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-1.6" x2="-3.1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.7" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.55" x2="3.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.1" y1="-1.2" x2="3.1" y2="1.25" width="0.2032" layer="21"/>
<wire x1="3.1" y1="1.25" x2="2.7" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.4" layer="21" style="longdash"/>
<smd name="C" x="-1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<smd name="A" x="1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="EIA3216-KIT">
<description>&lt;h3&gt;EIA3216-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-1" y1="-1.2" x2="-3" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="-1.2" x2="-3" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="3" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="-0.8" x2="3" y2="0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="0.8" x2="2.6" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<smd name="A" x="1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="CS5490">
<wire x1="-33.02" y1="17.78" x2="2.54" y2="17.78" width="0.254" layer="94"/>
<wire x1="2.54" y1="17.78" x2="2.54" y2="-15.24" width="0.254" layer="94"/>
<wire x1="2.54" y1="-15.24" x2="-33.02" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-33.02" y1="-15.24" x2="-33.02" y2="17.78" width="0.254" layer="94"/>
<text x="-20.32" y="-1.524" size="1.778" layer="95">&gt;NAME</text>
<text x="-20.32" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="D0" x="5.08" y="12.7" length="short" direction="out" rot="R180"/>
<pin name="RX" x="5.08" y="5.08" length="short" direction="in" rot="R180"/>
<pin name="TX" x="5.08" y="2.54" length="short" direction="out" rot="R180"/>
<pin name="XIN" x="5.08" y="0" length="short" direction="in" rot="R180"/>
<pin name="XOUT" x="5.08" y="-2.54" length="short" direction="out" rot="R180"/>
<pin name="VREF+" x="5.08" y="-5.08" length="short" direction="out" rot="R180"/>
<pin name="VREF-" x="5.08" y="-7.62" length="short" direction="in" rot="R180"/>
<pin name="!RESET" x="5.08" y="-10.16" length="short" direction="in" rot="R180"/>
<pin name="IIN-" x="-35.56" y="12.7" length="short" direction="in"/>
<pin name="IIN+" x="-35.56" y="7.62" length="short" direction="in"/>
<pin name="VIN+" x="-35.56" y="-2.54" length="short" direction="in"/>
<pin name="VIN-" x="-35.56" y="-7.62" length="short" direction="in"/>
<pin name="VDDA" x="-15.24" y="20.32" length="short" direction="in" rot="R270"/>
<pin name="MODE" x="-7.62" y="20.32" length="short" direction="in" rot="R270"/>
<pin name="VDDD" x="-22.86" y="20.32" length="short" direction="pwr" rot="R270"/>
<pin name="GNDA" x="-10.16" y="-17.78" length="short" direction="pwr" rot="R90"/>
</symbol>
<symbol name="MEU1S0503ZC">
<wire x1="-10.16" y1="5.08" x2="10.16" y2="5.08" width="0.4064" layer="94"/>
<wire x1="10.16" y1="5.08" x2="10.16" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="-10.16" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="-10.16" y1="-7.62" x2="-10.16" y2="5.08" width="0.4064" layer="94"/>
<text x="-10.16" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<text x="-8.636" y="-6.731" size="1.27" layer="94">DC/DC CONVERTER</text>
<pin name="+VIN" x="-12.7" y="2.54" length="short" direction="pas"/>
<pin name="-VIN" x="-12.7" y="-2.54" length="short" direction="pas"/>
<pin name="+VOUT" x="12.7" y="2.54" length="short" direction="pas" rot="R180"/>
<pin name="-VOUT" x="12.7" y="-2.54" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="SFH610A-3">
<wire x1="-6.985" y1="5.08" x2="9.525" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-6.985" y1="-5.08" x2="9.525" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="9.525" y1="5.08" x2="9.525" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-6.985" y1="5.08" x2="-6.985" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-3.175" y1="-2.54" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-3.175" y1="2.54" x2="0" y2="2.54" width="0.1524" layer="94"/>
<wire x1="2.032" y1="-1.143" x2="3.429" y2="0.254" width="0.1524" layer="94"/>
<wire x1="3.429" y1="0.254" x2="2.54" y2="-0.127" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-0.127" x2="3.048" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="3.048" y1="-0.635" x2="3.429" y2="0.254" width="0.1524" layer="94"/>
<wire x1="3.302" y1="1.397" x2="2.413" y2="1.016" width="0.1524" layer="94"/>
<wire x1="2.413" y1="1.016" x2="2.921" y2="0.508" width="0.1524" layer="94"/>
<wire x1="2.921" y1="0.508" x2="3.302" y2="1.397" width="0.1524" layer="94"/>
<wire x1="1.905" y1="0" x2="3.302" y2="1.397" width="0.1524" layer="94"/>
<wire x1="1.27" y1="1.27" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="-1.27" x2="-3.175" y2="1.27" width="0.254" layer="94"/>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.254" layer="94"/>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="1.27" width="0.254" layer="94"/>
<wire x1="-4.445" y1="-1.27" x2="-3.175" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-3.175" y1="-1.27" x2="-3.175" y2="1.27" width="0.254" layer="94"/>
<wire x1="-3.175" y1="-1.27" x2="-1.905" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-3.175" y1="-2.54" x2="-3.175" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="-3.175" y1="2.54" x2="-3.175" y2="1.27" width="0.1524" layer="94"/>
<wire x1="-3.175" y1="-2.54" x2="-7.62" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-3.175" y1="2.54" x2="-7.62" y2="2.54" width="0.1524" layer="94"/>
<wire x1="7.62" y1="2.54" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0" x2="7.366" y2="-2.286" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-2.54" x2="10.16" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="7.62" y1="2.54" x2="10.16" y2="2.54" width="0.1524" layer="94"/>
<wire x1="6.858" y1="-1.016" x2="7.366" y2="-2.286" width="0.1524" layer="94"/>
<wire x1="7.366" y1="-2.286" x2="7.62" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="7.366" y1="-2.286" x2="6.096" y2="-1.778" width="0.1524" layer="94"/>
<wire x1="6.096" y1="-1.778" x2="6.858" y2="-1.016" width="0.1524" layer="94"/>
<circle x="-3.175" y="2.54" radius="0.254" width="0.4064" layer="94"/>
<circle x="-3.175" y="-2.54" radius="0.254" width="0.4064" layer="94"/>
<text x="-6.985" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.985" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="4.699" y1="-2.54" x2="5.461" y2="2.54" layer="94"/>
<pin name="AC1" x="-10.16" y="2.54" visible="pad" length="short" direction="pas"/>
<pin name="AC2" x="-10.16" y="-2.54" visible="pad" length="short" direction="pas"/>
<pin name="E" x="12.7" y="-2.54" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="C" x="12.7" y="2.54" visible="pad" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="VTX-214-003-105">
<wire x1="1.27" y1="5.207" x2="1.27" y2="-7.747" width="0.254" layer="94"/>
<circle x="-2.921" y="-8.636" radius="0.127" width="0.3048" layer="94"/>
<circle x="5.461" y="-5.842" radius="0.127" width="0.3048" layer="94"/>
<text x="-2.54" y="7.366" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-10.795" size="1.778" layer="96">&gt;VALUE</text>
<text x="-3.175" y="-2.54" size="1.27" layer="94" rot="R90">MAINS</text>
<rectangle x1="-2.286" y1="-7.62" x2="0.254" y2="5.08" layer="94"/>
<pin name="L" x="-5.08" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="N" x="-5.08" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="-VE" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="2" rot="R180"/>
<pin name="+VE" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="2" rot="R180"/>
<wire x1="3.81" y1="3.81" x2="6.35" y2="3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="3.81" y1="-6.35" x2="6.35" y2="-6.35" width="0.254" layer="94"/>
</symbol>
<symbol name="L-EU">
<text x="-1.4986" y="-3.81" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="3.302" y="-3.81" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.016" y1="-3.556" x2="1.016" y2="3.556" layer="94"/>
<pin name="2" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
<pin name="1" x="0" y="5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
</symbol>
<symbol name="S216S01F">
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="1.016" width="0.1524" layer="94"/>
<wire x1="5.08" y1="1.016" x2="4.318" y2="1.016" width="0.1524" layer="94"/>
<wire x1="4.318" y1="1.27" x2="4.318" y2="0.762" width="0.1524" layer="94"/>
<wire x1="4.318" y1="0.254" x2="4.318" y2="0" width="0.1524" layer="94"/>
<wire x1="4.318" y1="0" x2="4.318" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="4.318" y1="-0.762" x2="4.318" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="4.318" y1="-1.016" x2="4.318" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="4.318" y1="0" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="4.826" y1="0.254" x2="4.318" y2="0" width="0.1524" layer="94"/>
<wire x1="4.318" y1="0" x2="4.826" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="4.826" y1="-0.254" x2="4.826" y2="0.254" width="0.1524" layer="94"/>
<wire x1="4.318" y1="-1.016" x2="5.08" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-1.016" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-1.016" x2="5.08" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-7.62" y1="5.08" x2="-7.62" y2="2.54" width="0.254" layer="94"/>
<wire x1="-7.62" y1="2.54" x2="-7.62" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-2.54" x2="-7.62" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-5.08" x2="7.62" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="6.35" y2="2.54" width="0.1524" layer="94"/>
<wire x1="6.35" y1="2.54" x2="7.874" y2="2.54" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="6.35" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="6.35" y1="-2.54" x2="7.62" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-5.08" x2="7.62" y2="5.08" width="0.254" layer="94"/>
<wire x1="7.62" y1="5.08" x2="-7.62" y2="5.08" width="0.254" layer="94"/>
<wire x1="6.35" y1="2.54" x2="6.35" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="2.54" x2="-7.62" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-7.62" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0.762" x2="-0.254" y2="-0.508" width="0.2032" layer="94"/>
<wire x1="-0.254" y1="-0.508" x2="-0.254" y2="1.27" width="0.2032" layer="94"/>
<wire x1="-0.254" y1="1.27" x2="2.794" y2="-0.762" width="0.2032" layer="94"/>
<circle x="6.35" y="2.54" radius="0.127" width="0.254" layer="94"/>
<circle x="6.35" y="-2.54" radius="0.127" width="0.254" layer="94"/>
<text x="-7.62" y="6.35" size="1.778" layer="95" font="vector">&gt;NAME</text>
<text x="-7.62" y="-7.62" size="1.778" layer="96" font="vector">&gt;VALUE</text>
<rectangle x1="5.842" y1="0.254" x2="6.858" y2="0.508" layer="94"/>
<rectangle x1="-6.35" y1="-1.016" x2="-3.81" y2="-0.762" layer="94"/>
<pin name="A" x="-10.16" y="2.54" visible="pad" length="short" direction="pas"/>
<pin name="K" x="-10.16" y="-2.54" visible="pad" length="short" direction="pas"/>
<pin name="DS1" x="10.16" y="2.54" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="DS2" x="10.16" y="-2.54" visible="pad" length="short" direction="pas" rot="R180"/>
<polygon width="0.1524" layer="94">
<vertex x="-6.35" y="1.016"/>
<vertex x="-3.81" y="1.016"/>
<vertex x="-5.08" y="-0.762"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="6.35" y="0.254"/>
<vertex x="5.842" y="-0.508"/>
<vertex x="6.858" y="-0.508"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="1.778" y="0.508"/>
<vertex x="1.27" y="-0.254"/>
<vertex x="2.794" y="-0.762"/>
</polygon>
</symbol>
<symbol name="NPN">
<wire x1="2.54" y1="2.54" x2="0.508" y2="1.524" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-1.524" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="1.27" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.778" y2="-1.524" width="0.1524" layer="94"/>
<wire x1="1.54" y1="-2.04" x2="0.308" y2="-1.424" width="0.1524" layer="94"/>
<wire x1="1.524" y1="-2.413" x2="2.286" y2="-2.413" width="0.254" layer="94"/>
<wire x1="2.286" y1="-2.413" x2="1.778" y2="-1.778" width="0.254" layer="94"/>
<wire x1="1.778" y1="-1.778" x2="1.524" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.524" y1="-2.286" x2="1.905" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.905" y1="-2.286" x2="1.778" y2="-2.032" width="0.254" layer="94"/>
<text x="-10.16" y="7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="5.08" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-2.54" x2="0.508" y2="2.54" layer="94"/>
<pin name="B" x="-2.54" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="E" x="2.54" y="-5.08" visible="off" length="short" direction="pas" swaplevel="3" rot="R90"/>
<pin name="C" x="2.54" y="5.08" visible="off" length="short" direction="pas" swaplevel="2" rot="R270"/>
</symbol>
<symbol name="PHOTON">
<wire x1="-11.43" y1="-30.48" x2="11.43" y2="-30.48" width="0.254" layer="94"/>
<wire x1="11.43" y1="-30.48" x2="12.7" y2="-27.94" width="0.254" layer="94"/>
<wire x1="12.7" y1="-27.94" x2="12.7" y2="30.48" width="0.254" layer="94"/>
<wire x1="12.7" y1="30.48" x2="5.08" y2="30.48" width="0.254" layer="94"/>
<wire x1="5.08" y1="30.48" x2="5.08" y2="33.02" width="0.254" layer="94"/>
<wire x1="5.08" y1="33.02" x2="-5.08" y2="33.02" width="0.254" layer="94"/>
<wire x1="-5.08" y1="33.02" x2="-5.08" y2="30.48" width="0.254" layer="94"/>
<wire x1="-5.08" y1="30.48" x2="-12.7" y2="30.48" width="0.254" layer="94"/>
<wire x1="-12.7" y1="30.48" x2="-12.7" y2="-27.94" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-27.94" x2="-11.43" y2="-30.48" width="0.254" layer="94"/>
<pin name="VIN" x="-17.78" y="27.94" length="middle" direction="pwr"/>
<pin name="GND@2" x="-17.78" y="22.86" length="middle" direction="pwr"/>
<pin name="TX" x="-17.78" y="17.78" length="middle"/>
<pin name="RX" x="-17.78" y="12.7" length="middle"/>
<pin name="WKP" x="-17.78" y="7.62" length="middle"/>
<pin name="DAC" x="-17.78" y="2.54" length="middle"/>
<pin name="A5" x="-17.78" y="-2.54" length="middle"/>
<pin name="A4" x="-17.78" y="-7.62" length="middle"/>
<pin name="A3" x="-17.78" y="-12.7" length="middle"/>
<pin name="A2" x="-17.78" y="-17.78" length="middle"/>
<pin name="A1" x="-17.78" y="-22.86" length="middle"/>
<pin name="A0" x="-17.78" y="-27.94" length="middle"/>
<pin name="3V3" x="17.78" y="27.94" length="middle" direction="pwr" rot="R180"/>
<pin name="!RST" x="17.78" y="22.86" length="middle" rot="R180"/>
<pin name="VBAT" x="17.78" y="17.78" length="middle" direction="pwr" rot="R180"/>
<pin name="GND@21" x="17.78" y="12.7" length="middle" direction="pwr" rot="R180"/>
<pin name="D7" x="17.78" y="7.62" length="middle" rot="R180"/>
<pin name="D6" x="17.78" y="2.54" length="middle" rot="R180"/>
<pin name="D5" x="17.78" y="-2.54" length="middle" rot="R180"/>
<pin name="D4" x="17.78" y="-7.62" length="middle" rot="R180"/>
<pin name="D3" x="17.78" y="-12.7" length="middle" rot="R180"/>
<pin name="D2" x="17.78" y="-17.78" length="middle" rot="R180"/>
<pin name="D1" x="17.78" y="-22.86" length="middle" rot="R180"/>
<pin name="D0" x="17.78" y="-27.94" length="middle" rot="R180"/>
<text x="-4.826" y="-3.302" size="2.032" layer="97">Photon</text>
</symbol>
<symbol name="FUSED">
<wire x1="-3.81" y1="-0.762" x2="3.81" y2="-0.762" width="0.254" layer="94"/>
<wire x1="3.81" y1="0.762" x2="-3.81" y2="0.762" width="0.254" layer="94"/>
<wire x1="3.81" y1="-0.762" x2="3.81" y2="0.762" width="0.254" layer="94"/>
<wire x1="-3.81" y1="0.762" x2="-3.81" y2="-0.762" width="0.254" layer="94"/>
<text x="-3.81" y="1.397" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-2.921" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1B" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="1A" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2A" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2B" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="MCP16301T-I/CHY">
<pin name="VIN" x="-15.24" y="2.54" length="middle" direction="in"/>
<pin name="BOOST" x="0" y="12.7" length="middle" direction="pas" rot="R270"/>
<pin name="EN" x="-15.24" y="-5.08" length="middle" direction="in"/>
<pin name="GND" x="-15.24" y="-10.16" length="middle" direction="pas"/>
<pin name="VFB" x="15.24" y="-7.62" length="middle" direction="out" rot="R180"/>
<pin name="SW" x="15.24" y="2.54" length="middle" direction="out" rot="R180"/>
<wire x1="-10.16" y1="7.62" x2="-10.16" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="-10.16" y1="-15.24" x2="10.16" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="10.16" y1="-15.24" x2="10.16" y2="7.62" width="0.4064" layer="94"/>
<wire x1="10.16" y1="7.62" x2="-10.16" y2="7.62" width="0.4064" layer="94"/>
<text x="-4.8006" y="9.6012" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-5.5118" y="-18.3642" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
</symbol>
<symbol name="CAPH">
<pin name="2" x="7.62" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="0" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<wire x1="3.4798" y1="0" x2="3.4798" y2="1.905" width="0.2032" layer="94"/>
<wire x1="4.1148" y1="0" x2="4.1148" y2="1.905" width="0.2032" layer="94"/>
<text x="-1.8034" y="-7.3406" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
<text x="-0.9144" y="2.7686" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-1.8034" y="-7.3406" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
<text x="-0.9144" y="2.7686" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-0.9144" y="2.7686" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-0.9144" y="2.7686" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-1.8034" y="-7.3406" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
<text x="-0.9144" y="2.7686" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<wire x1="3.4798" y1="-1.905" x2="3.4798" y2="0" width="0.2032" layer="94"/>
<wire x1="4.1148" y1="-1.905" x2="4.1148" y2="0" width="0.2032" layer="94"/>
<wire x1="4.1148" y1="0" x2="5.08" y2="0" width="0.2032" layer="94"/>
<wire x1="2.54" y1="0" x2="3.4798" y2="0" width="0.2032" layer="94"/>
<text x="-1.8034" y="-7.3406" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
<text x="-0.9144" y="2.7686" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
</symbol>
<symbol name="UCC28722">
<pin name="GND" x="15.24" y="-2.54" length="middle" direction="pas" rot="R180"/>
<pin name="CBC" x="-15.24" y="-10.16" length="middle" direction="pas"/>
<pin name="CS" x="15.24" y="5.08" length="middle" direction="in" rot="R180"/>
<pin name="VDD" x="-15.24" y="-2.54" length="middle" direction="pwr"/>
<pin name="DRV" x="-15.24" y="5.08" length="middle" direction="out"/>
<pin name="VS" x="15.24" y="-10.16" length="middle" direction="in" rot="R180"/>
<wire x1="-10.16" y1="7.62" x2="-10.16" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="-10.16" y1="-15.24" x2="10.16" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="10.16" y1="-15.24" x2="10.16" y2="7.62" width="0.4064" layer="94"/>
<wire x1="10.16" y1="7.62" x2="-10.16" y2="7.62" width="0.4064" layer="94"/>
<text x="-4.8006" y="9.6012" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-5.5118" y="-18.3642" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
</symbol>
<symbol name="CAP_POL">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202" cap="flat"/>
<wire x1="-2.4669" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.376341" cap="flat"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.253" y1="0.668" x2="-1.364" y2="0.795" layer="94"/>
<rectangle x1="-1.872" y1="0.287" x2="-1.745" y2="1.176" layer="94"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CS5490">
<gates>
<gate name="G$1" symbol="CS5490" x="15.24" y="2.54"/>
</gates>
<devices>
<device name="" package="SOIC16N">
<connects>
<connect gate="G$1" pin="!RESET" pad="3"/>
<connect gate="G$1" pin="D0" pad="12"/>
<connect gate="G$1" pin="GNDA" pad="10"/>
<connect gate="G$1" pin="IIN+" pad="5"/>
<connect gate="G$1" pin="IIN-" pad="4"/>
<connect gate="G$1" pin="MODE" pad="15"/>
<connect gate="G$1" pin="RX" pad="14"/>
<connect gate="G$1" pin="TX" pad="13"/>
<connect gate="G$1" pin="VDDA" pad="11"/>
<connect gate="G$1" pin="VDDD" pad="16"/>
<connect gate="G$1" pin="VIN+" pad="6"/>
<connect gate="G$1" pin="VIN-" pad="7"/>
<connect gate="G$1" pin="VREF+" pad="9"/>
<connect gate="G$1" pin="VREF-" pad="8"/>
<connect gate="G$1" pin="XIN" pad="2"/>
<connect gate="G$1" pin="XOUT" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MEU1S0503ZC" prefix="DC">
<gates>
<gate name="G$1" symbol="MEU1S0503ZC" x="0" y="0"/>
</gates>
<devices>
<device name="D" package="4-PIN-ZIF">
<connects>
<connect gate="G$1" pin="+VIN" pad="2"/>
<connect gate="G$1" pin="+VOUT" pad="4"/>
<connect gate="G$1" pin="-VIN" pad="1"/>
<connect gate="G$1" pin="-VOUT" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="" constant="no"/>
<attribute name="OC_NEWARK" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SFH610A-3" prefix="OK">
<gates>
<gate name="G$1" symbol="SFH610A-3" x="0" y="0"/>
</gates>
<devices>
<device name="SMD" package="DIL4-SMD">
<connects>
<connect gate="G$1" pin="AC1" pad="1"/>
<connect gate="G$1" pin="AC2" pad="2"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="E" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="VISHAY/TELEFUNKEN" constant="no"/>
<attribute name="MPN" value="SFH6206-3" constant="no"/>
<attribute name="OC_FARNELL" value="1469585" constant="no"/>
<attribute name="OC_NEWARK" value="58K2214" constant="no"/>
</technology>
</technologies>
</device>
<device name="TH" package="DIL04">
<connects>
<connect gate="G$1" pin="AC1" pad="1"/>
<connect gate="G$1" pin="AC2" pad="2"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="E" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="SFH610A-3" constant="no"/>
<attribute name="OC_FARNELL" value="1469569" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VTX-214-003-105" prefix="TR" uservalue="yes">
<gates>
<gate name="1" symbol="VTX-214-003-105" x="0" y="0"/>
</gates>
<devices>
<device name="" package="VTX-214-003-105">
<connects>
<connect gate="1" pin="+VE" pad="4"/>
<connect gate="1" pin="-VE" pad="3"/>
<connect gate="1" pin="L" pad="1"/>
<connect gate="1" pin="N" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RLB0914-4R7ML" prefix="L" uservalue="yes">
<gates>
<gate name="G$1" symbol="L-EU" x="0" y="0"/>
</gates>
<devices>
<device name="A" package="RLB0914-4R7ML">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="S216S01F" prefix="K">
<description>SSR</description>
<gates>
<gate name="G$1" symbol="S216S01F" x="0" y="0"/>
</gates>
<devices>
<device name="A" package="S216S01F">
<connects>
<connect gate="G$1" pin="A" pad="3"/>
<connect gate="G$1" pin="DS1" pad="1"/>
<connect gate="G$1" pin="DS2" pad="2"/>
<connect gate="G$1" pin="K" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="2N3904" prefix="T">
<description>&lt;b&gt;NPN TRANSISTOR&lt;/b&gt;</description>
<gates>
<gate name="G1" symbol="NPN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO92">
<connects>
<connect gate="G1" pin="B" pad="2"/>
<connect gate="G1" pin="C" pad="1"/>
<connect gate="G1" pin="E" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PHOTON">
<gates>
<gate name="G$1" symbol="PHOTON" x="0" y="0"/>
</gates>
<devices>
<device name="_WITH_HEADERS" package="PHOTON">
<connects>
<connect gate="G$1" pin="!RST" pad="23"/>
<connect gate="G$1" pin="3V3" pad="24"/>
<connect gate="G$1" pin="A0" pad="12"/>
<connect gate="G$1" pin="A1" pad="11"/>
<connect gate="G$1" pin="A2" pad="10"/>
<connect gate="G$1" pin="A3" pad="9"/>
<connect gate="G$1" pin="A4" pad="8"/>
<connect gate="G$1" pin="A5" pad="7"/>
<connect gate="G$1" pin="D0" pad="13"/>
<connect gate="G$1" pin="D1" pad="14"/>
<connect gate="G$1" pin="D2" pad="15"/>
<connect gate="G$1" pin="D3" pad="16"/>
<connect gate="G$1" pin="D4" pad="17"/>
<connect gate="G$1" pin="D5" pad="18"/>
<connect gate="G$1" pin="D6" pad="19"/>
<connect gate="G$1" pin="D7" pad="20"/>
<connect gate="G$1" pin="DAC" pad="6"/>
<connect gate="G$1" pin="GND@2" pad="2"/>
<connect gate="G$1" pin="GND@21" pad="21"/>
<connect gate="G$1" pin="RX" pad="4"/>
<connect gate="G$1" pin="TX" pad="3"/>
<connect gate="G$1" pin="VBAT" pad="22"/>
<connect gate="G$1" pin="VIN" pad="1"/>
<connect gate="G$1" pin="WKP" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_WITH_STACKABLE_HEADERS" package="PHOTON_STACKABLE">
<connects>
<connect gate="G$1" pin="!RST" pad="#23 23 @23"/>
<connect gate="G$1" pin="3V3" pad="#24 24 @24"/>
<connect gate="G$1" pin="A0" pad="#12 12 @12"/>
<connect gate="G$1" pin="A1" pad="#11 11 @11"/>
<connect gate="G$1" pin="A2" pad="#10 10 @10"/>
<connect gate="G$1" pin="A3" pad="#9 9 @9"/>
<connect gate="G$1" pin="A4" pad="#8 8 @8"/>
<connect gate="G$1" pin="A5" pad="#7 7 @7"/>
<connect gate="G$1" pin="D0" pad="#13 13 @13"/>
<connect gate="G$1" pin="D1" pad="#14 14 @14"/>
<connect gate="G$1" pin="D2" pad="#15 15 @15"/>
<connect gate="G$1" pin="D3" pad="#16 16 @16"/>
<connect gate="G$1" pin="D4" pad="#17 17 @17"/>
<connect gate="G$1" pin="D5" pad="#18 18 @18"/>
<connect gate="G$1" pin="D6" pad="#19 19 @19"/>
<connect gate="G$1" pin="D7" pad="#20 20 @20"/>
<connect gate="G$1" pin="DAC" pad="#6 6 @6"/>
<connect gate="G$1" pin="GND@2" pad="#2 2 @2"/>
<connect gate="G$1" pin="GND@21" pad="#21 21 @21"/>
<connect gate="G$1" pin="RX" pad="#4 4 @4"/>
<connect gate="G$1" pin="TX" pad="#3 3 @3"/>
<connect gate="G$1" pin="VBAT" pad="#22 22 @22"/>
<connect gate="G$1" pin="VIN" pad="#1 1 @1"/>
<connect gate="G$1" pin="WKP" pad="#5 5 @5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SH32" prefix="F" uservalue="yes">
<description>&lt;b&gt;FUSE HOLDER&lt;/b&gt;&lt;p&gt; 6 x 32 mm, SH contact, SHH3N Schukat, 102071 Wickmann (Buerklin)</description>
<gates>
<gate name="G$1" symbol="FUSED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SH32">
<connects>
<connect gate="G$1" pin="1A" pad="1A"/>
<connect gate="G$1" pin="1B" pad="1B"/>
<connect gate="G$1" pin="2A" pad="2A"/>
<connect gate="G$1" pin="2B" pad="2B"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="10207101009" constant="no"/>
<attribute name="OC_FARNELL" value="811786" constant="no"/>
<attribute name="OC_NEWARK" value="76R6904" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MCP16301T-I/CHY" prefix="U">
<description>IC, BUCK, ADJ, 0.6A, 6SOT23</description>
<gates>
<gate name="A" symbol="MCP16301T-I/CHY" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT95P290X145-6N">
<connects>
<connect gate="A" pin="BOOST" pad="1"/>
<connect gate="A" pin="EN" pad="4"/>
<connect gate="A" pin="GND" pad="2"/>
<connect gate="A" pin="SW" pad="6"/>
<connect gate="A" pin="VFB" pad="3"/>
<connect gate="A" pin="VIN" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="MPN" value="MCP16301T-I/CHY" constant="no"/>
<attribute name="OC_FARNELL" value="2009288" constant="no"/>
<attribute name="OC_NEWARK" value="58T3650" constant="no"/>
<attribute name="PACKAGE" value="SOT23-6" constant="no"/>
<attribute name="SUPPLIER" value="Microchip" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ECQ" prefix="C" uservalue="yes">
<description>Stacked Metallized Plastic Film Capacitor</description>
<gates>
<gate name="A" symbol="CAPH" x="0" y="0" swaplevel="1"/>
</gates>
<devices>
<device name="" package="CAPM1500X500X1200">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A102ML">
<attribute name="MPN" value="ECQU2A102ML " constant="no"/>
<attribute name="OC_FARNELL" value="2281860 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1965 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.0010UF" constant="no"/>
</technology>
<technology name="U2A103KLA">
<attribute name="MPN" value="ECQU2A103KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673302 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9846 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value=" 0.01UF" constant="no"/>
</technology>
<technology name="U2A103ML">
<attribute name="MPN" value="ECQU2A103ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198290 " constant="no"/>
<attribute name="OC_NEWARK" value="25M9114 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.01UF" constant="no"/>
</technology>
<technology name="U2A152ML">
<attribute name="MPN" value="ECQU2A152ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281864 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1995 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.0015UF" constant="no"/>
</technology>
<technology name="U2A153KLA">
<attribute name="MPN" value="ECQU2A153KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673303 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9850 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="0.015UF" constant="no"/>
</technology>
<technology name="U2A153ML">
<attribute name="MPN" value="ECQU2A153ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281865 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1998 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.015UF" constant="no"/>
</technology>
<technology name="U2A222ML">
<attribute name="MPN" value="ECQU2A222ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281868 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2022 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.0022UF" constant="no"/>
</technology>
<technology name="U2A223KLA">
<attribute name="MPN" value="ECQU2A223KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673304 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9853 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value=" 0.022UF" constant="no"/>
</technology>
<technology name="U2A223ML">
<attribute name="MPN" value="ECQU2A223ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198291 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7585 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.022UF" constant="no"/>
</technology>
<technology name="U2A273ML">
<attribute name="MPN" value="ECQU2A273ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281871 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2040 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.027UF" constant="no"/>
</technology>
<technology name="U2A332ML">
<attribute name="MPN" value="ECQU2A332ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281873 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2048 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.0033UF" constant="no"/>
</technology>
<technology name="U2A332MLA">
<attribute name="MPN" value="ECQU2A332MLA" constant="no"/>
<attribute name="OC_FARNELL" value="2281874 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2049 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.0033UF" constant="no"/>
</technology>
<technology name="U2A472ML">
<attribute name="MPN" value="ECQU2A472ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281876 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2069 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.0047UF" constant="no"/>
</technology>
<technology name="U2A682ML">
<attribute name="MPN" value="ECQU2A682ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281883 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2089 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.0068UF" constant="no"/>
</technology>
<technology name="U3A103MG">
<attribute name="MPN" value="ECQU3A103MG" constant="no"/>
<attribute name="OC_FARNELL" value="1854808 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5681 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.01UF" constant="no"/>
</technology>
<technology name="U3A153MG">
<attribute name="MPN" value="ECQU3A153MG" constant="no"/>
<attribute name="OC_FARNELL" value="1854809 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.015UF" constant="no"/>
</technology>
<technology name="U3A223MG">
<attribute name="MPN" value="ECQU3A223MG" constant="no"/>
<attribute name="OC_FARNELL" value="1854810 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5686 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.022UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L15" package="CAPM1500X600X1350">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A333ML">
<attribute name="MPN" value="ECQU2A333ML " constant="no"/>
<attribute name="OC_FARNELL" value="Unknown" constant="no"/>
<attribute name="OC_NEWARK" value=" 53W8302 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.033UF" constant="no"/>
</technology>
<technology name="U2A473KLA">
<attribute name="MPN" value="ECQU2A473KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673306 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9857 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="0.047UF" constant="no"/>
</technology>
<technology name="U2A473ML">
<attribute name="MPN" value="ECQU2A473ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198292 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7588 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value=" 0.047UF" constant="no"/>
</technology>
<technology name="U3A333MG">
<attribute name="MPN" value="ECQU3A333MG" constant="no"/>
<attribute name="OC_FARNELL" value="1854812 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5688 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value=" 0.033UF" constant="no"/>
</technology>
<technology name="U3A473MG">
<attribute name="MPN" value="ECQU3A473MG" constant="no"/>
<attribute name="OC_FARNELL" value="Unknown " constant="no"/>
<attribute name="OC_NEWARK" value="53W8305 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value=" 0.047UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L15-T8" package="CAPM1500X800X1550">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U3A104MG">
<attribute name="MPN" value="ECQU3A104MG " constant="no"/>
<attribute name="OC_FARNELL" value="1854815 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5682 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.1UF" constant="no"/>
</technology>
<technology name="U3A683MG">
<attribute name="MPN" value="ECQU3A683MG" constant="no"/>
<attribute name="OC_FARNELL" value="1854814 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5692 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.068UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5" package="CAPM1750X450X1200">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A563ML">
<attribute name="MPN" value="ECQU2A563ML " constant="no"/>
<attribute name="OC_FARNELL" value="2281881" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W2082 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.056UF" constant="no"/>
</technology>
<technology name="U2A683KLA">
<attribute name="MPN" value="ECQU2A683KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673307 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9860 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10 %" constant="no"/>
<attribute name="VALUE" value="0.068UF" constant="no"/>
</technology>
<technology name="U2A683ML">
<attribute name="MPN" value="ECQU2A683ML" constant="no"/>
<attribute name="OC_FARNELL" value="Unknown " constant="no"/>
<attribute name="OC_NEWARK" value="49W2092 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.068UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T5" package="CAPM1750X500X1250">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF104K">
<attribute name="MPN" value="ECQUAAF104K " constant="no"/>
<attribute name="OC_FARNELL" value="2281852" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W1952 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="0.10UF" constant="no"/>
</technology>
<technology name="UAAF104M">
<attribute name="MPN" value="ECQUAAF104M" constant="no"/>
<attribute name="OC_FARNELL" value="1907246 " constant="no"/>
<attribute name="OC_NEWARK" value="58T1725 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value=" 0.1UF" constant="no"/>
</technology>
<technology name="UAAF104MA">
<attribute name="MPN" value="ECQUAAF104MA" constant="no"/>
<attribute name="OC_FARNELL" value="1907253 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.1UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T5.5" package="CAPM1750X550X1250">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A104KL">
<attribute name="MPN" value="ECQU2A104KL " constant="no"/>
<attribute name="OC_FARNELL" value="2281861 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1970 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10 %" constant="no"/>
<attribute name="VALUE" value="0.010UF" constant="no"/>
</technology>
<technology name="U2A104KLA">
<attribute name="MPN" value="ECQU2A104KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673308 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9847 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10 %" constant="no"/>
<attribute name="VALUE" value="0.1UF" constant="no"/>
</technology>
<technology name="U2A104ML">
<attribute name="MPN" value="ECQU2A104ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198295 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7582 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 % " constant="no"/>
<attribute name="VALUE" value="0.1UF" constant="no"/>
</technology>
<technology name="U2A823ML">
<attribute name="MPN" value="ECQU2A823ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281884 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2102 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 % " constant="no"/>
<attribute name="VALUE" value="0.082UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T6" package="CAPM1750X600X1350">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF154M">
<attribute name="MPN" value="ECQUAAF154M " constant="no"/>
<attribute name="OC_FARNELL" value="1907247 " constant="no"/>
<attribute name="OC_NEWARK" value="58T1729 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.15UF" constant="no"/>
</technology>
<technology name="UAAF154MA">
<attribute name="MPN" value="ECQUAAF154MA" constant="no"/>
<attribute name="OC_FARNELL" value="1907254 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.15UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T6.5" package="CAPM1750X650X1500">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A154KLA">
<attribute name="MPN" value="ECQU2A154KLA " constant="no"/>
<attribute name="OC_FARNELL" value="1673310 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9851 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="0.15UF" constant="no"/>
</technology>
<technology name="U2A154ML">
<attribute name="MPN" value="ECQU2A154ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198296 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7584 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value=" 0.15UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T7.5" package="CAPM1750X750X1450">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF224K">
<attribute name="MPN" value=" ECQUAAF224K " constant="no"/>
<attribute name="OC_FARNELL" value="2281856 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1957 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC" constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value=" 0.22UF" constant="no"/>
</technology>
<technology name="UAAF224M">
<attribute name="MPN" value="ECQUAAF224M" constant="no"/>
<attribute name="OC_FARNELL" value="1907248 " constant="no"/>
<attribute name="OC_NEWARK" value="58T1731 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC" constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.22UF" constant="no"/>
</technology>
<technology name="UAAF224MA">
<attribute name="MPN" value="ECQUAAF224MA" constant="no"/>
<attribute name="OC_FARNELL" value="1907255 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC" constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.22UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T8" package="CAPM1750X800X1650">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A224KLA">
<attribute name="MPN" value="ECQU2A224KLA " constant="no"/>
<attribute name="OC_FARNELL" value="1673311 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9854 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value=" ±10%" constant="no"/>
<attribute name="VALUE" value="0.22UF" constant="no"/>
</technology>
<technology name="U2A224ML">
<attribute name="MPN" value="ECQU2A224ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198297 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7586 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value=" ±20%" constant="no"/>
<attribute name="VALUE" value="0.22UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T9" package="CAPM1750X900X1650">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF334K">
<attribute name="MPN" value="ECQUAAF334K " constant="no"/>
<attribute name="OC_FARNELL" value="2281858 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1960 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="0.33UF" constant="no"/>
</technology>
<technology name="UAAF334M">
<attribute name="MPN" value="ECQUAAF334M" constant="no"/>
<attribute name="OC_FARNELL" value="1907249 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value=" 0.33UF" constant="no"/>
</technology>
<technology name="UAAF334MA">
<attribute name="MPN" value="ECQUAAF334MA" constant="no"/>
<attribute name="OC_FARNELL" value="1907257 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.33UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L17.5-T9.5" package="CAPM1750X950X1800">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A274ML">
<attribute name="MPN" value="ECQU2A274ML " constant="no"/>
<attribute name="OC_FARNELL" value="2281872 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2044 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value=" ±20%" constant="no"/>
<attribute name="VALUE" value="0.27UF" constant="no"/>
</technology>
<technology name="U2A334KLA">
<attribute name="MPN" value="ECQU2A334KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673313 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9856 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value=" ±10%" constant="no"/>
<attribute name="VALUE" value="0.33UF" constant="no"/>
</technology>
<technology name="U2A334ML">
<attribute name="MPN" value="ECQU2A334ML" constant="no"/>
<attribute name="OC_FARNELL" value="Unknown " constant="no"/>
<attribute name="OC_NEWARK" value="53W8303 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value=" ±20%" constant="no"/>
<attribute name="VALUE" value="0.33UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L18-T8" package="CAPM1800X800X1700">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U3A154MG">
<attribute name="MPN" value=" ECQU3A154MG " constant="no"/>
<attribute name="OC_FARNELL" value="1854816" constant="no"/>
<attribute name="OC_NEWARK" value=" 23T5685 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC" constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.15UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L18-T9" package="CAPM1800X900X1800">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U3A224MG">
<attribute name="MPN" value="ECQU3A224MG " constant="no"/>
<attribute name="OC_FARNELL" value="1854817 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5687 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 % " constant="no"/>
<attribute name="VALUE" value=" 0.22UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L25.5" package="CAPM2550X1050X2000">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A564KLA">
<attribute name="MPN" value="ECQU2A564KLA " constant="no"/>
<attribute name="OC_FARNELL" value="1673315 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9859 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="0.56UF" constant="no"/>
</technology>
<technology name="U2A564ML">
<attribute name="MPN" value="ECQU2A564ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281882 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2085 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.56UF" constant="no"/>
</technology>
<technology name="U2A684KLA">
<attribute name="MPN" value="ECQU2A684KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673316 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9861 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="0.68UF" constant="no"/>
</technology>
<technology name="U2A684ML">
<attribute name="MPN" value="ECQU2A684ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198301 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7590 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.68UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L25.5-T12" package="CAPM2550X1200X2200">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A105KL">
<attribute name="MPN" value="ECQU2A105KL " constant="no"/>
<attribute name="OC_FARNELL" value="2281862" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W1974 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="1UF" constant="no"/>
</technology>
<technology name="U2A105KLA">
<attribute name="MPN" value="ECQU2A105KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673317 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9848 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="1UF" constant="no"/>
</technology>
<technology name="U2A105ML">
<attribute name="MPN" value="ECQU2A105ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198302 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7583 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="1UF" constant="no"/>
</technology>
<technology name="U2A824ML">
<attribute name="MPN" value="ECQU2A824ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281885 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2106 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.82UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L25.5-T8.5" package="CAPM2550X850X1800">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A394ML">
<attribute name="MPN" value="ECQU2A394ML " constant="no"/>
<attribute name="OC_FARNELL" value="2281875 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2065 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.39UF" constant="no"/>
</technology>
<technology name="U2A474KL">
<attribute name="MPN" value="ECQU2A474KL" constant="no"/>
<attribute name="OC_FARNELL" value="2281877 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2074 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10 %" constant="no"/>
<attribute name="VALUE" value="0.47UF" constant="no"/>
</technology>
<technology name="U2A474KLA">
<attribute name="MPN" value="ECQU2A474KLA" constant="no"/>
<attribute name="OC_FARNELL" value="1673314 " constant="no"/>
<attribute name="OC_NEWARK" value="39P9858 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10 %" constant="no"/>
<attribute name="VALUE" value=" 0.47UF" constant="no"/>
</technology>
<technology name="U2A474ML">
<attribute name="MPN" value="ECQU2A474ML" constant="no"/>
<attribute name="OC_FARNELL" value="1198299 " constant="no"/>
<attribute name="OC_NEWARK" value="01M7589 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.47UF" constant="no"/>
</technology>
<technology name="U2A474MLA">
<attribute name="MPN" value="ECQU2A474MLA" constant="no"/>
<attribute name="OC_FARNELL" value="2281878 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2075 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.47UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L26" package="CAPM2600X1000X1750">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF684M">
<attribute name="MPN" value=" ECQUAAF684M " constant="no"/>
<attribute name="OC_FARNELL" value="1907251" constant="no"/>
<attribute name="OC_NEWARK" value=" 58T1737 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC" constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.68UF" constant="no"/>
</technology>
<technology name="UAAF684MA">
<attribute name="MPN" value="ECQUAAF684MA" constant="no"/>
<attribute name="OC_FARNELL" value="1907259 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC" constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.68UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L26-T10.5" package="CAPM2600X1050X2050">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U3A474MG">
<attribute name="MPN" value="ECQU3A474MG " constant="no"/>
<attribute name="OC_FARNELL" value="1854819 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5691 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="0.47UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L26-T12" package="CAPM2600X1200X1950">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF105K">
<attribute name="MPN" value="ECQUAAF105K " constant="no"/>
<attribute name="OC_FARNELL" value="2281853 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1953 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value="1UF" constant="no"/>
</technology>
<technology name="UAAF105M">
<attribute name="MPN" value="ECQUAAF105M" constant="no"/>
<attribute name="OC_FARNELL" value="1907252 " constant="no"/>
<attribute name="OC_NEWARK" value="58T1727 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="1UF" constant="no"/>
</technology>
<technology name="UAAF105MA">
<attribute name="MPN" value="ECQUAAF105MA" constant="no"/>
<attribute name="OC_FARNELL" value="1907260 " constant="no"/>
<attribute name="OC_NEWARK" value="Unknown " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="1UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L26-T12.5" package="CAPM2600X1250X2250">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U3A684MG">
<attribute name="MPN" value="ECQU3A684MG " constant="no"/>
<attribute name="OC_FARNELL" value="1854820 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5693 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 % " constant="no"/>
<attribute name="VALUE" value=" 0.68UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L26-T8.5" package="CAPM2600X850X1550">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF474K">
<attribute name="MPN" value="ECQUAAF474K " constant="no"/>
<attribute name="OC_FARNELL" value="2281859" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W1961 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±10%" constant="no"/>
<attribute name="VALUE" value=" 0.47UF" constant="no"/>
</technology>
<technology name="UAAF474M">
<attribute name="MPN" value="ECQUAAF474M" constant="no"/>
<attribute name="OC_FARNELL" value="1907250 " constant="no"/>
<attribute name="OC_NEWARK" value="58T1735 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value=" 0.47UF" constant="no"/>
</technology>
<technology name="UAAF474MA">
<attribute name="MPN" value="ECQUAAF474MA" constant="no"/>
<attribute name="OC_FARNELL" value="1907258 " constant="no"/>
<attribute name="OC_NEWARK" value="58T1736 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="0.47UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L26-T9" package="CAPM2600X900X1900">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U3A334MG">
<attribute name="MPN" value="ECQU3A334MG " constant="no"/>
<attribute name="OC_FARNELL" value="1854818 " constant="no"/>
<attribute name="OC_NEWARK" value="23T5689 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value=" 0.33UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L27" package="CAPM2700X1650X2600">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U3A105MG">
<attribute name="MPN" value="ECQU3A105MG " constant="no"/>
<attribute name="OC_FARNELL" value="1854821 " constant="no"/>
<attribute name="OC_NEWARK" value="53W8304 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="250V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20 %" constant="no"/>
<attribute name="VALUE" value="1UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L30.5" package="CAPM3050X1650X2650">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A125ML">
<attribute name="MPN" value="ECQU2A125ML " constant="no"/>
<attribute name="OC_FARNELL" value="2281863 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1991 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="1.2UF" constant="no"/>
</technology>
<technology name="U2A155ML">
<attribute name="MPN" value="ECQU2A155ML" constant="no"/>
<attribute name="OC_FARNELL" value="2281866 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2003 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="1.5UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L30.5-T19" package="CAPM3050X1900X3000">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="U2A225ML">
<attribute name="MPN" value="ECQU2A225ML " constant="no"/>
<attribute name="OC_FARNELL" value="2281869 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2032 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="2.2UF" constant="no"/>
</technology>
<technology name="U2A225MLA">
<attribute name="MPN" value="ECQU2A225MLA" constant="no"/>
<attribute name="OC_FARNELL" value="2281870 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2033 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="2.2UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L31" package="CAPM3100X1200X2250">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF155M">
<attribute name="MPN" value="ECQUAAF155M " constant="no"/>
<attribute name="OC_FARNELL" value="2281854" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W1956 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="±20%" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="275V" constant="no"/>
<attribute name="VALUE" value="1.5UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L31-T14.5" package="CAPM3100X1450X2500">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="UAAF225M">
<attribute name="MPN" value="ECQUAAF225M " constant="no"/>
<attribute name="OC_FARNELL" value="2281857 " constant="no"/>
<attribute name="OC_NEWARK" value="49W1959 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 275V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±20%" constant="no"/>
<attribute name="VALUE" value="2.2UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L10.2" package="CAPM1020X400X1000">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="SUPPLIER">
<attribute name="MPN" value="ECQV1224JM9 " constant="no"/>
<attribute name="OC_FARNELL" value="2282053 " constant="no"/>
<attribute name="OC_NEWARK" value="53W3629 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 100V" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±5%" constant="no"/>
<attribute name="VALUE" value="0.22UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L7.5" package="CAPM750X450X800">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="V1104JM2">
<attribute name="MPN" value="ECQV1104JM2 " constant="no"/>
<attribute name="OC_FARNELL" value="2281912 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2382 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="100VDC" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±5%" constant="no"/>
<attribute name="VALUE" value="0.10UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L7.3" package="CAPM730X400X600">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="V1H104JL9">
<attribute name="MPN" value=" ECQV1H104JL9 " constant="no"/>
<attribute name="OC_FARNELL" value="2282048" constant="no"/>
<attribute name="OC_NEWARK" value=" 53W3624 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 50VDC" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC" constant="no"/>
<attribute name="TOLERANCE" value=" ±5%" constant="no"/>
<attribute name="VALUE" value="0.10UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L7.3-T4" package="CAPM730X400X900">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="V1H104JLW">
<attribute name="MPN" value="ECQV1H104JLW " constant="no"/>
<attribute name="OC_FARNELL" value="2281887 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2131 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 50VDC" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±5%" constant="no"/>
<attribute name="VALUE" value=" 0.10UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L7.3-T4.8" package="CAPM730X480X650">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="V1H224JL2">
<attribute name="MPN" value="ECQV1H224JL2 " constant="no"/>
<attribute name="OC_FARNELL" value="2281896 " constant="no"/>
<attribute name="OC_NEWARK" value="49W2188 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 50VDC" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±5%" constant="no"/>
<attribute name="VALUE" value="0.22UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L7.3-T3.2" package="CAPM730X320X600">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="V1H473JL2">
<attribute name="MPN" value="ECQV1H473JL2 " constant="no"/>
<attribute name="OC_FARNELL" value="2281901" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W2229 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="50VDC" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value="±5%" constant="no"/>
<attribute name="VALUE" value="0.047UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L7.3-T6.0" package="CAPM730X600X830">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="V1H474JL2">
<attribute name="MPN" value="ECQV1H474JL2 " constant="no"/>
<attribute name="OC_FARNELL" value="2281904" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W2234 " constant="no"/>
<attribute name="RATEDVOLTAGE" value="50VDC" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value=" ±5%" constant="no"/>
<attribute name="VALUE" value="0.47UF" constant="no"/>
</technology>
</technologies>
</device>
<device name="-L7.3-T6.0-H11.3" package="CAPM730X600X1130">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="V1H474JLW">
<attribute name="MPN" value="ECQV1H474JLW " constant="no"/>
<attribute name="OC_FARNELL" value="2281903" constant="no"/>
<attribute name="OC_NEWARK" value=" 49W2233 " constant="no"/>
<attribute name="RATEDVOLTAGE" value=" 50VDC" constant="no"/>
<attribute name="SUPPLIER" value="PANASONIC " constant="no"/>
<attribute name="TOLERANCE" value=" ±5%" constant="no"/>
<attribute name="VALUE" value="0.47UF" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="UCC28722" prefix="U">
<description>Constant-Voltage, Constant-Current Controller With Primary-Side Regulation, BJT Drive</description>
<gates>
<gate name="A" symbol="UCC28722" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT95P290X145-6N">
<connects>
<connect gate="A" pin="CBC" pad="1"/>
<connect gate="A" pin="CS" pad="4"/>
<connect gate="A" pin="DRV" pad="3"/>
<connect gate="A" pin="GND" pad="5"/>
<connect gate="A" pin="VDD" pad="2"/>
<connect gate="A" pin="VS" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="MPN" value="UCC28722" constant="no"/>
<attribute name="OC_FARNELL" value="2400944" constant="no"/>
<attribute name="PACKAGE" value="SOT23-6" constant="no"/>
<attribute name="SUPPLIER" value="Ti" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="KSC5026M" prefix="Q">
<description>&lt;b&gt;NPN Transistor&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="NPN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO126">
<connects>
<connect gate="G$1" pin="B" pad="3"/>
<connect gate="G$1" pin="C" pad="2"/>
<connect gate="G$1" pin="E" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP_POL" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor Polarized&lt;/b&gt;
These are standard SMD and PTH capacitors. Normally 10uF, 47uF, and 100uF in electrolytic and tantalum varieties. Always verify the external diameter of the through hole cap, it varies with capacity, voltage, and manufacturer. The EIA devices should be standard.</description>
<gates>
<gate name="G$1" symbol="CAP_POL" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="EIA3216">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528" package="EIA3528">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CPOL-RADIAL-100UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CPOL-RADIAL-10UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="7343" package="EIA7343">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="G" package="PANASONIC_G">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="E" package="PANASONIC_E">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="C" package="PANASONIC_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="F80" package="NIPPON_F80">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="D" package="PANASONIC_D">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH3" package="CPOL-RADIAL-1000UF-63V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH4" package="CPOL-RADIAL-1000UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="VISHAY_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="H13" package="PANASONIC_H13">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="6032" package="EIA6032">
<connects>
<connect gate="G$1" pin="+" pad="P$1"/>
<connect gate="G$1" pin="-" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EN_J2" package="EN_J2">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528-KIT" package="EIA3528-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206-KIT" package="EIA3216-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
We've spent an enormous amount of time creating and checking these footprints and parts. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; CC v3.0 Share-Alike You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="HC49U-V">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-2.921" y1="-2.286" x2="2.921" y2="-2.286" width="0.4064" layer="21"/>
<wire x1="-2.921" y1="2.286" x2="2.921" y2="2.286" width="0.4064" layer="21"/>
<wire x1="-2.921" y1="-1.778" x2="2.921" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.778" x2="-2.921" y2="1.778" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.778" x2="2.921" y2="-1.778" width="0.1524" layer="21" curve="-180"/>
<wire x1="2.921" y1="2.286" x2="2.921" y2="-2.286" width="0.4064" layer="21" curve="-180"/>
<wire x1="-2.921" y1="2.286" x2="-2.921" y2="-2.286" width="0.4064" layer="21" curve="180"/>
<wire x1="-2.921" y1="1.778" x2="-2.921" y2="-1.778" width="0.1524" layer="21" curve="180"/>
<wire x1="-0.254" y1="0.889" x2="0.254" y2="0.889" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.889" x2="0.254" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.889" x2="-0.254" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.889" x2="-0.254" y2="0.889" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0.889" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.889" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.27" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-2.413" y="0" drill="0.8128"/>
<pad name="2" x="2.413" y="0" drill="0.8128"/>
<text x="-5.08" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.81" y1="-2.794" x2="3.81" y2="2.794" layer="43"/>
<rectangle x1="-4.318" y1="-2.54" x2="-3.81" y2="2.54" layer="43"/>
<rectangle x1="-4.826" y1="-2.286" x2="-4.318" y2="2.286" layer="43"/>
<rectangle x1="-5.334" y1="-1.778" x2="-4.826" y2="1.778" layer="43"/>
<rectangle x1="-5.588" y1="-1.27" x2="-5.334" y2="1.016" layer="43"/>
<rectangle x1="3.81" y1="-2.54" x2="4.318" y2="2.54" layer="43"/>
<rectangle x1="4.318" y1="-2.286" x2="4.826" y2="2.286" layer="43"/>
<rectangle x1="4.826" y1="-1.778" x2="5.334" y2="1.778" layer="43"/>
<rectangle x1="5.334" y1="-1.016" x2="5.588" y2="1.016" layer="43"/>
</package>
<package name="TC38H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-1.397" y1="1.651" x2="1.397" y2="1.651" width="0.1524" layer="21"/>
<wire x1="1.27" y1="9.906" x2="1.524" y2="9.652" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="9.652" x2="-1.27" y2="9.906" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.27" y1="9.906" x2="1.27" y2="9.906" width="0.1524" layer="21"/>
<wire x1="1.397" y1="1.651" x2="1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.524" y1="2.032" x2="1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.524" y1="2.032" x2="1.524" y2="9.652" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="1.651" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="2.032" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="2.032" x2="-1.524" y2="9.652" width="0.1524" layer="21"/>
<wire x1="1.397" y1="2.032" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="0.5588" y1="0.7112" x2="0.508" y2="0.762" width="0.4064" layer="21"/>
<wire x1="0.508" y1="0.762" x2="0.508" y2="1.143" width="0.4064" layer="21"/>
<wire x1="-0.508" y1="0.762" x2="-0.508" y2="1.016" width="0.4064" layer="21"/>
<wire x1="-0.5588" y1="0.7112" x2="-0.508" y2="0.762" width="0.4064" layer="21"/>
<wire x1="0.635" y1="0.635" x2="1.27" y2="0" width="0.1524" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="-1.27" y2="0" width="0.1524" layer="51"/>
<wire x1="-0.762" y1="5.588" x2="-0.762" y2="5.207" width="0.1524" layer="21"/>
<wire x1="0.762" y1="5.207" x2="-0.762" y2="5.207" width="0.1524" layer="21"/>
<wire x1="0.762" y1="5.207" x2="0.762" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="5.588" x2="0.762" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="5.969" x2="0" y2="5.969" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="4.826" x2="0" y2="4.826" width="0.1524" layer="21"/>
<wire x1="0" y1="4.826" x2="0" y2="4.318" width="0.1524" layer="21"/>
<wire x1="0" y1="4.826" x2="0.762" y2="4.826" width="0.1524" layer="21"/>
<wire x1="0" y1="5.969" x2="0" y2="6.477" width="0.1524" layer="21"/>
<wire x1="0" y1="5.969" x2="0.762" y2="5.969" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" diameter="1.6764"/>
<pad name="2" x="1.27" y="0" drill="0.8128" diameter="1.6764"/>
<text x="-1.905" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.175" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="1.016" x2="1.778" y2="10.414" layer="43"/>
</package>
<package name="TC26H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-0.889" y1="1.651" x2="0.889" y2="1.651" width="0.1524" layer="21"/>
<wire x1="0.762" y1="7.747" x2="1.016" y2="7.493" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.016" y1="7.493" x2="-0.762" y2="7.747" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.762" y1="7.747" x2="0.762" y2="7.747" width="0.1524" layer="21"/>
<wire x1="0.889" y1="1.651" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-0.889" y1="1.651" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="0.508" y1="0.762" x2="0.508" y2="1.143" width="0.4064" layer="21"/>
<wire x1="-0.508" y1="0.762" x2="-0.508" y2="1.27" width="0.4064" layer="21"/>
<wire x1="0.635" y1="0.635" x2="1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="-1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.508" y1="4.953" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.953" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="5.334" x2="0" y2="5.334" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.191" x2="0" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0" y2="3.683" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0.508" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0" y2="5.842" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0.508" y2="5.334" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="0.889" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" diameter="1.6764"/>
<pad name="2" x="1.27" y="0" drill="0.8128" diameter="1.6764"/>
<text x="-1.397" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="2.667" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="0.762" x2="1.778" y2="8.382" layer="43"/>
</package>
<package name="HC49UP">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-5.1091" y1="1.143" x2="-3.429" y2="2.0321" width="0.0508" layer="21" curve="-55.770993" cap="flat"/>
<wire x1="-5.715" y1="1.143" x2="-5.715" y2="2.159" width="0.1524" layer="21"/>
<wire x1="3.429" y1="2.032" x2="5.1091" y2="1.143" width="0.0508" layer="21" curve="-55.772485" cap="flat"/>
<wire x1="5.715" y1="1.143" x2="5.715" y2="2.159" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-1.27" x2="-3.429" y2="-1.27" width="0.0508" layer="21"/>
<wire x1="3.429" y1="-2.032" x2="-3.429" y2="-2.032" width="0.0508" layer="21"/>
<wire x1="-3.429" y1="1.27" x2="3.429" y2="1.27" width="0.0508" layer="21"/>
<wire x1="5.461" y1="-2.413" x2="-5.461" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-0.381" x2="6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="5.715" y1="0.381" x2="6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="6.477" y1="-0.381" x2="6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="5.461" y1="-2.413" x2="5.715" y2="-2.159" width="0.1524" layer="21" curve="90"/>
<wire x1="5.715" y1="-1.143" x2="5.715" y2="1.143" width="0.1524" layer="51"/>
<wire x1="5.715" y1="-2.159" x2="5.715" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-1.27" x2="3.9826" y2="-1.143" width="0.0508" layer="21" curve="25.842828" cap="flat"/>
<wire x1="3.429" y1="1.27" x2="3.9826" y2="1.143" width="0.0508" layer="21" curve="-25.842828" cap="flat"/>
<wire x1="3.429" y1="-2.032" x2="5.109" y2="-1.1429" width="0.0508" layer="21" curve="55.771157" cap="flat"/>
<wire x1="3.9826" y1="-1.143" x2="3.9826" y2="1.143" width="0.0508" layer="51" curve="128.314524" cap="flat"/>
<wire x1="5.1091" y1="-1.143" x2="5.1091" y2="1.143" width="0.0508" layer="51" curve="68.456213" cap="flat"/>
<wire x1="-5.1091" y1="-1.143" x2="-3.429" y2="-2.032" width="0.0508" layer="21" curve="55.772485" cap="flat"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.9826" y2="1.143" width="0.0508" layer="51" curve="-128.314524" cap="flat"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.429" y2="-1.27" width="0.0508" layer="21" curve="25.842828" cap="flat"/>
<wire x1="-3.9826" y1="1.143" x2="-3.429" y2="1.27" width="0.0508" layer="21" curve="-25.842828" cap="flat"/>
<wire x1="-6.477" y1="-0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.1091" y1="-1.143" x2="-5.1091" y2="1.143" width="0.0508" layer="51" curve="-68.456213" cap="flat"/>
<wire x1="-5.715" y1="-1.143" x2="-5.715" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="-0.381" x2="-5.715" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="0.381" x2="-5.715" y2="1.143" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="-2.159" x2="-5.715" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.159" x2="-5.461" y2="-2.413" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.715" y1="-0.381" x2="-6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-3.429" y1="2.032" x2="3.429" y2="2.032" width="0.0508" layer="21"/>
<wire x1="5.461" y1="2.413" x2="-5.461" y2="2.413" width="0.1524" layer="21"/>
<wire x1="5.461" y1="2.413" x2="5.715" y2="2.159" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.715" y1="2.159" x2="-5.461" y2="2.413" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.254" y1="0.635" x2="-0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.635" x2="0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.635" x2="0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.635" x2="-0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.016" y2="0" width="0.0508" layer="21"/>
<wire x1="0.635" y1="0.635" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.016" y2="0" width="0.0508" layer="21"/>
<smd name="1" x="-4.826" y="0" dx="5.334" dy="1.9304" layer="1"/>
<smd name="2" x="4.826" y="0" dx="5.334" dy="1.9304" layer="1"/>
<text x="-5.715" y="2.794" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.715" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.604" y1="-3.048" x2="6.604" y2="3.048" layer="43"/>
</package>
<package name="HC49US">
<description>&lt;B&gt;CRYSTAL&lt;/B&gt;</description>
<wire x1="-3.429" y1="-2.286" x2="3.429" y2="-2.286" width="0.2032" layer="21"/>
<wire x1="3.429" y1="2.286" x2="-3.429" y2="2.286" width="0.2032" layer="21"/>
<wire x1="3.429" y1="2.286" x2="3.429" y2="-2.286" width="0.2032" layer="21" curve="-180"/>
<wire x1="-3.429" y1="2.286" x2="-3.429" y2="-2.286" width="0.2032" layer="21" curve="180"/>
<pad name="1" x="-2.54" y="0" drill="0.7" diameter="1.651" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651" rot="R90"/>
<text x="-5.08" y="-3.937" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.08" y="2.667" size="1.27" layer="25" ratio="10">&gt;NAME</text>
</package>
<package name="CRYSTAL-32KHZ-SMD">
<smd name="X1" x="-1.27" y="0" dx="1" dy="2.5" layer="1"/>
<smd name="X2" x="1.27" y="0" dx="1" dy="2.5" layer="1"/>
<smd name="SHEILD" x="0" y="5.08" dx="2.5" dy="6" layer="1"/>
<text x="-0.635" y="8.255" size="0.4064" layer="25">&gt;Name</text>
<text x="-0.635" y="-1.905" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="CRYSTAL-SMD-5X3">
<wire x1="-0.6" y1="1.6" x2="0.6" y2="1.6" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.3" x2="2.5" y2="-0.3" width="0.2032" layer="21"/>
<wire x1="0.6" y1="-1.6" x2="-0.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="0.3" x2="-2.5" y2="-0.3" width="0.2032" layer="21"/>
<smd name="1" x="-1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="3" x="1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="4" x="-1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="2" x="1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<text x="-2.54" y="1.905" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="CRYSTAL-32KHZ-SMD_EPSON_MC146">
<wire x1="0.2" y1="0" x2="7.2" y2="0" width="0.127" layer="51"/>
<wire x1="7.2" y1="0" x2="7.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="7.2" y1="1.5" x2="0.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.2" y1="1.5" x2="0.2" y2="0" width="0.127" layer="51"/>
<wire x1="6.2" y1="1.4" x2="5.9" y2="1.4" width="0.127" layer="21"/>
<wire x1="5.9" y1="1.4" x2="5.9" y2="0.1" width="0.127" layer="21"/>
<wire x1="5.9" y1="0.1" x2="6.2" y2="0.1" width="0.127" layer="21"/>
<wire x1="1.3" y1="1.4" x2="1.9" y2="1.4" width="0.127" layer="21"/>
<wire x1="1.3" y1="0.1" x2="1.9" y2="0.1" width="0.127" layer="21"/>
<smd name="P$1" x="0.6" y="0.3" dx="1.2" dy="0.6" layer="1"/>
<smd name="P$2" x="0.6" y="1.2" dx="1.2" dy="0.6" layer="1"/>
<smd name="NC2" x="6.9" y="0.3" dx="1.2" dy="0.6" layer="1"/>
<smd name="NC1" x="6.9" y="1.2" dx="1.2" dy="0.6" layer="1"/>
</package>
<package name="CRYSTAL-SMD-10.5X4.8-2PIN">
<wire x1="-6.2" y1="1.5" x2="-6.2" y2="2.4" width="0.127" layer="21"/>
<wire x1="-6.2" y1="2.4" x2="6.2" y2="2.4" width="0.127" layer="21"/>
<wire x1="6.2" y1="2.4" x2="6.2" y2="1.5" width="0.127" layer="21"/>
<wire x1="-6.2" y1="-1.5" x2="-6.2" y2="-2.4" width="0.127" layer="21"/>
<wire x1="-6.2" y1="-2.4" x2="6.2" y2="-2.4" width="0.127" layer="21"/>
<wire x1="6.2" y1="-2.4" x2="6.2" y2="-1.5" width="0.127" layer="21"/>
<smd name="P$1" x="-4.3" y="0" dx="5.5" dy="1.5" layer="1"/>
<smd name="P$2" x="4.3" y="0" dx="5.5" dy="1.5" layer="1"/>
</package>
<package name="CAP-PTH-SMALL">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651"/>
<text x="0.508" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="0.254" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="CAP-PTH-SMALL2">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="3.81" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="-1.27" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651"/>
<text x="-1.27" y="1.905" size="0.6096" layer="25">&gt;Name</text>
<text x="-1.27" y="-2.54" size="0.6096" layer="27">&gt;Value</text>
</package>
<package name="0805">
<wire x1="-0.3" y1="0.6" x2="0.3" y2="0.6" width="0.1524" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="-0.6" width="0.1524" layer="21"/>
<smd name="1" x="-0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<smd name="2" x="0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<text x="-0.762" y="0.8255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="CAP-PTH-LARGE">
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.2032" layer="21"/>
<pad name="1" x="-4.826" y="0" drill="0.9" diameter="1.905"/>
<pad name="2" x="4.572" y="0" drill="0.9" diameter="1.905"/>
<text x="-0.762" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.016" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="GRM43D">
<wire x1="2.25" y1="1.6" x2="1.1" y2="1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="1.6" x2="-1.1" y2="1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="1.6" x2="-2.25" y2="1.6" width="0.127" layer="51"/>
<wire x1="-2.25" y1="1.6" x2="-2.25" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-2.25" y1="-1.6" x2="-1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="-1.6" x2="1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="-1.6" x2="2.25" y2="-1.6" width="0.127" layer="51"/>
<wire x1="2.25" y1="-1.6" x2="2.25" y2="1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="1.6" x2="1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="1.6" x2="-1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-2.3" y1="1.8" x2="2.3" y2="1.8" width="0.127" layer="21"/>
<wire x1="-2.3" y1="-1.8" x2="2.3" y2="-1.8" width="0.127" layer="21"/>
<smd name="A" x="1.927" y="0" dx="3.2" dy="1.65" layer="1" rot="R90"/>
<smd name="C" x="-1.927" y="0" dx="3.2" dy="1.65" layer="1" rot="R90"/>
<text x="-2" y="2" size="0.4064" layer="25">&gt;NAME</text>
<text x="0" y="-2" size="0.4064" layer="27" rot="R180">&gt;VALUE</text>
<rectangle x1="-2.2" y1="-1.6" x2="-1.1" y2="1.6" layer="51"/>
<rectangle x1="1.1" y1="-1.6" x2="2.2" y2="1.6" layer="51"/>
</package>
<package name="0603-CAP">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<wire x1="0" y1="0.0305" x2="0" y2="-0.0305" width="0.5588" layer="21"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="0402-CAP">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="0" y1="0.0305" x2="0" y2="-0.0305" width="0.4064" layer="21"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="CAP-PTH-5MM">
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.5" y="0" drill="0.7" diameter="1.651"/>
<text x="-0.762" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.016" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="AXIAL-5MM">
<wire x1="-1.14" y1="0.762" x2="1.14" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0.762" x2="1.14" y2="0" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0" x2="1.14" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="-0.762" x2="-1.14" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="-0.762" x2="-1.14" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="0" x2="-1.14" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0" x2="1.394" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="0" x2="-1.394" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-2.5" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="2.5" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.17" size="0.4" layer="25">&gt;Name</text>
<text x="-1.032" y="-0.208" size="0.4" layer="21" ratio="15">&gt;Value</text>
</package>
<package name="1210">
<wire x1="-1.6" y1="1.3" x2="1.6" y2="1.3" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.3" x2="1.6" y2="-1.3" width="0.127" layer="51"/>
<wire x1="1.6" y1="-1.3" x2="-1.6" y2="-1.3" width="0.127" layer="51"/>
<wire x1="-1.6" y1="-1.3" x2="-1.6" y2="1.3" width="0.127" layer="51"/>
<wire x1="-1.6" y1="1.3" x2="1.6" y2="1.3" width="0.2032" layer="21"/>
<wire x1="-1.6" y1="-1.3" x2="1.6" y2="-1.3" width="0.2032" layer="21"/>
<smd name="1" x="-1.6" y="0" dx="1.2" dy="2" layer="1"/>
<smd name="2" x="1.6" y="0" dx="1.2" dy="2" layer="1"/>
<text x="-0.8" y="0.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.9" y="-0.7" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1206">
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-0.965" y1="0.787" x2="0.965" y2="0.787" width="0.1016" layer="51"/>
<wire x1="-0.965" y1="-0.787" x2="0.965" y2="-0.787" width="0.1016" layer="51"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-1.27" y="1.143" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.397" y="-1.524" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-1.7018" y1="-0.8509" x2="-0.9517" y2="0.8491" layer="51"/>
<rectangle x1="0.9517" y1="-0.8491" x2="1.7018" y2="0.8509" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
<package name="CTZ3">
<description>CTZ3 Series land pattern for variable capacitor - CTZ3E-50C-W1-PF</description>
<wire x1="-1.6" y1="1.4" x2="-1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-1.6" y1="-2.25" x2="1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.4" x2="1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-0.5" y1="0" x2="0.5" y2="0" width="0.127" layer="51"/>
<wire x1="-1.6" y1="1.4" x2="-1" y2="2.2" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.4" x2="1" y2="2.2" width="0.127" layer="51"/>
<wire x1="-1" y1="2.2" x2="1" y2="2.2" width="0.127" layer="51"/>
<wire x1="0" y1="0.8" x2="0" y2="-0.8" width="0.127" layer="51"/>
<wire x1="-0.8" y1="0" x2="0.8" y2="0" width="0.127" layer="51"/>
<wire x1="-1.05" y1="2.25" x2="-1.7" y2="1.45" width="0.127" layer="21"/>
<wire x1="-1.7" y1="1.45" x2="-1.7" y2="-2.35" width="0.127" layer="21"/>
<wire x1="-1.7" y1="-2.35" x2="-1.05" y2="-2.35" width="0.127" layer="21"/>
<wire x1="1.05" y1="2.25" x2="1.7" y2="1.4" width="0.127" layer="21"/>
<wire x1="1.7" y1="1.4" x2="1.7" y2="-2.35" width="0.127" layer="21"/>
<wire x1="1.7" y1="-2.35" x2="1.05" y2="-2.35" width="0.127" layer="21"/>
<smd name="+" x="0" y="2.05" dx="1.5" dy="1.2" layer="1"/>
<smd name="-" x="0" y="-2.05" dx="1.5" dy="1.2" layer="1"/>
<text x="-2" y="3" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2" y="-3.4" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="CAP-PTH-SMALL-KIT">
<description>&lt;h3&gt;CAP-PTH-SMALL-KIT&lt;/h3&gt;
Commonly used for small ceramic capacitors. Like our 0.1uF (http://www.sparkfun.com/products/8375) or 22pF caps (http://www.sparkfun.com/products/8571).&lt;br&gt;
&lt;br&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.254" layer="21"/>
<wire x1="-2.667" y1="1.27" x2="2.667" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.667" y1="1.27" x2="2.667" y2="-1.27" width="0.254" layer="21"/>
<wire x1="2.667" y1="-1.27" x2="-2.667" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-2.667" y1="-1.27" x2="-2.667" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-1.397" y="0" drill="1.016" diameter="2.032" stop="no"/>
<pad name="2" x="1.397" y="0" drill="1.016" diameter="2.032" stop="no"/>
<polygon width="0.127" layer="30">
<vertex x="-1.4021" y="-0.9475" curve="-90"/>
<vertex x="-2.357" y="-0.0178" curve="-90.011749"/>
<vertex x="-1.4046" y="0.9576" curve="-90"/>
<vertex x="-0.4546" y="-0.0204" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-1.4046" y="-0.4395" curve="-90.012891"/>
<vertex x="-1.8491" y="-0.0153" curve="-90"/>
<vertex x="-1.4046" y="0.452" curve="-90"/>
<vertex x="-0.9627" y="-0.0051" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="1.397" y="-0.9475" curve="-90"/>
<vertex x="0.4421" y="-0.0178" curve="-90.011749"/>
<vertex x="1.3945" y="0.9576" curve="-90"/>
<vertex x="2.3445" y="-0.0204" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="1.3945" y="-0.4395" curve="-90.012891"/>
<vertex x="0.95" y="-0.0153" curve="-90"/>
<vertex x="1.3945" y="0.452" curve="-90"/>
<vertex x="1.8364" y="-0.0051" curve="-90.012967"/>
</polygon>
</package>
<package name="AXIAL-0.3">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="3.81" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.032" y="-0.381" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="R2010">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.1524" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.1524" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="-1.027" y1="1.245" x2="1.027" y2="1.245" width="0.1524" layer="21"/>
<wire x1="-1.002" y1="-1.245" x2="1.016" y2="-1.245" width="0.1524" layer="21"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-2.54" y="1.5875" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.032" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
</package>
<package name="0603-RES">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2286" y1="-0.381" x2="0.2286" y2="0.381" layer="21"/>
</package>
<package name="0402-RES">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2032" y1="-0.3556" x2="0.2032" y2="0.3556" layer="21"/>
</package>
<package name="1/6W-RES">
<description>1/6W Thru-hole Resistor - *UNPROVEN*</description>
<wire x1="-1.55" y1="0.85" x2="-1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="-1.55" y1="-0.85" x2="1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="-0.85" x2="1.55" y2="0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="0.85" x2="-1.55" y2="0.85" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.762"/>
<pad name="2" x="2.5" y="0" drill="0.762"/>
<text x="-1.2662" y="0.9552" size="0.6096" layer="25">&gt;NAME</text>
<text x="-1.423" y="-0.4286" size="0.8128" layer="21" ratio="15">&gt;VALUE</text>
</package>
<package name="R2512">
<wire x1="-2.362" y1="1.473" x2="2.387" y2="1.473" width="0.1524" layer="51"/>
<wire x1="-2.362" y1="-1.473" x2="2.387" y2="-1.473" width="0.1524" layer="51"/>
<smd name="1" x="-2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<smd name="2" x="2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.2004" y1="-1.5494" x2="-2.3505" y2="1.5507" layer="51"/>
<rectangle x1="2.3622" y1="-1.5494" x2="3.2121" y2="1.5507" layer="51"/>
</package>
<package name="AXIAL-0.4">
<description>1/4W Resistor, 0.4" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-3.15" y1="-1.2" x2="-3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3.15" y1="1.2" x2="3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="1.2" x2="3.15" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="-1.2" x2="-3.15" y2="-1.2" width="0.2032" layer="21"/>
<pad name="P$1" x="-5.08" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="5.08" y="0" drill="0.9" diameter="1.8796"/>
<text x="-3.175" y="1.905" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-2.286" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.5">
<description>1/2W Resistor, 0.5" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-4.5" y1="-1.65" x2="-4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="1.65" x2="4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="1.65" x2="4.5" y2="-1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-1.65" x2="-4.5" y2="-1.65" width="0.2032" layer="21"/>
<pad name="P$1" x="-6.35" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="6.35" y="0" drill="0.9" diameter="1.8796"/>
<text x="-4.445" y="2.54" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-3.429" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.6">
<description>1W Resistor, 0.6" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-5.75" y1="-2.25" x2="-5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="-5.75" y1="2.25" x2="5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="2.25" x2="5.75" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="-2.25" x2="-5.75" y2="-2.25" width="0.2032" layer="21"/>
<pad name="P$1" x="-7.62" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="7.62" y="0" drill="1.2" diameter="1.8796"/>
<text x="-5.715" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-4.064" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.8">
<description>2W Resistor, 0.8" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-7.75" y1="-2.5" x2="-7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-7.75" y1="2.5" x2="7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="2.5" x2="7.75" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="-2.5" x2="-7.75" y2="-2.5" width="0.2032" layer="21"/>
<pad name="P$1" x="-10.16" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="10.16" y="0" drill="1.2" diameter="1.8796"/>
<text x="-7.62" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-5.969" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.3-KIT">
<description>&lt;h3&gt;AXIAL-0.3-KIT&lt;/h3&gt;

Commonly used for 1/4W through-hole resistors. 0.3" pitch between holes.&lt;br&gt;
&lt;br&gt;

&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of the AXIAL-0.3 package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="0" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="-2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.254" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<pad name="P$2" x="3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.159" y="-0.762" size="1.27" layer="21" font="vector" ratio="15">&gt;Value</text>
<polygon width="0.127" layer="30">
<vertex x="3.8201" y="-0.9449" curve="-90"/>
<vertex x="2.8652" y="-0.0152" curve="-90.011749"/>
<vertex x="3.8176" y="0.9602" curve="-90"/>
<vertex x="4.7676" y="-0.0178" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="3.8176" y="-0.4369" curve="-90.012891"/>
<vertex x="3.3731" y="-0.0127" curve="-90"/>
<vertex x="3.8176" y="0.4546" curve="-90"/>
<vertex x="4.2595" y="-0.0025" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="-3.8075" y="-0.9525" curve="-90"/>
<vertex x="-4.7624" y="-0.0228" curve="-90.011749"/>
<vertex x="-3.81" y="0.9526" curve="-90"/>
<vertex x="-2.86" y="-0.0254" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-3.81" y="-0.4445" curve="-90.012891"/>
<vertex x="-4.2545" y="-0.0203" curve="-90"/>
<vertex x="-3.81" y="0.447" curve="-90"/>
<vertex x="-3.3681" y="-0.0101" curve="-90.012967"/>
</polygon>
</package>
<package name="EIA3216">
<wire x1="-1" y1="-1.2" x2="-2.5" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.2" x2="-2.5" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="-1.2" x2="2.5" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-0.8" x2="2.5" y2="0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.8" x2="2.1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<smd name="A" x="1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528">
<wire x1="-0.9" y1="-1.6" x2="-2.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-1.6" x2="-2.6" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.2" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-1.55" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="2.6" y2="1.25" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.25" x2="2.2" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.2032" layer="21" style="longdash"/>
<smd name="C" x="-1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<smd name="A" x="1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="CPOL-RADIAL-100UF-25V">
<wire x1="-0.635" y1="1.27" x2="-1.905" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="3.25" width="0.2032" layer="21"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="1.651" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-10UF-25V">
<wire x1="-0.762" y1="1.397" x2="-1.778" y2="1.397" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="2.5" width="0.2032" layer="21"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<text x="-0.889" y="1.524" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.905" y="-3.683" size="0.8128" layer="27">&gt;Value</text>
</package>
<package name="EIA7343">
<wire x1="-5" y1="2.5" x2="-2" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="2.5" x2="-5" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="-2.5" x2="-2" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="2" y1="2.5" x2="4" y2="2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="2.5" x2="5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="1.5" x2="5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="-1.5" x2="4" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="-2.5" x2="2" y2="-2.5" width="0.2032" layer="21"/>
<smd name="C" x="-3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<smd name="A" x="3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="-1.27" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="PANASONIC_G">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package G&lt;/b&gt;</description>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="-2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="1" x2="-5.1" y2="5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="1" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-1" x2="5.1" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="-1" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="-1" x2="4.85" y2="-1" width="0.2032" layer="21" curve="156.699401" cap="flat"/>
<wire x1="-4.85" y1="1" x2="4.85" y2="1" width="0.2032" layer="21" curve="-156.699401" cap="flat"/>
<wire x1="-3.25" y1="3.7" x2="-3.25" y2="-3.65" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="4.95" width="0.1016" layer="51"/>
<smd name="-" x="-4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<smd name="+" x="4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-5.85" y1="-0.45" x2="-4.9" y2="0.45" layer="51"/>
<rectangle x1="4.9" y1="-0.45" x2="5.85" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-3.3" y="3.6"/>
<vertex x="-4.05" y="2.75"/>
<vertex x="-4.65" y="1.55"/>
<vertex x="-4.85" y="0.45"/>
<vertex x="-4.85" y="-0.45"/>
<vertex x="-4.65" y="-1.55"/>
<vertex x="-4.05" y="-2.75"/>
<vertex x="-3.3" y="-3.6"/>
<vertex x="-3.3" y="3.55"/>
</polygon>
</package>
<package name="PANASONIC_E">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="-1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="0.9" x2="-4.1" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="0.9" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-0.9" x2="4.1" y2="-1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="-0.9" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="3.25" x2="-2.2" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.85" y1="0.9" x2="3.85" y2="0.9" width="0.2032" layer="21" curve="-153.684915" cap="flat"/>
<wire x1="-3.85" y1="-0.9" x2="3.85" y2="-0.9" width="0.2032" layer="21" curve="153.684915" cap="flat"/>
<circle x="0" y="0" radius="3.95" width="0.1016" layer="51"/>
<smd name="-" x="-3" y="0" dx="3.8" dy="1.4" layer="1"/>
<smd name="+" x="3" y="0" dx="3.8" dy="1.4" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-4.5" y1="-0.35" x2="-3.8" y2="0.35" layer="51"/>
<rectangle x1="3.8" y1="-0.35" x2="4.5" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.25" y="3.2"/>
<vertex x="-3" y="2.5"/>
<vertex x="-3.6" y="1.5"/>
<vertex x="-3.85" y="0.65"/>
<vertex x="-3.85" y="-0.65"/>
<vertex x="-3.55" y="-1.6"/>
<vertex x="-2.95" y="-2.55"/>
<vertex x="-2.25" y="-3.2"/>
<vertex x="-2.25" y="3.15"/>
</polygon>
</package>
<package name="PANASONIC_C">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.2032" layer="21"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.1016" layer="51"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.1016" layer="51"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="0.35" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-2.85" x2="-2.6" y2="-0.75" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="0.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="2.7" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="-1.75" width="0.1016" layer="51"/>
<wire x1="-2.4" y1="0.35" x2="2.45" y2="0.3" width="0.2032" layer="21" curve="-156.699401"/>
<wire x1="2.5" y1="-0.7" x2="-2.4" y2="-0.75" width="0.2032" layer="21" curve="-154.694887"/>
<circle x="0.05" y="-0.2" radius="2.5004" width="0.1016" layer="51"/>
<smd name="-" x="-1.8" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<smd name="+" x="1.9" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<text x="-2.6" y="2.7" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.6" y="-3.45" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="NIPPON_F80">
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.1016" layer="51"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="-3.3" x2="-3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="2" x2="3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="3.3" y1="2" x2="3.3" y2="-2" width="0.1016" layer="51"/>
<wire x1="-3.1" y1="0.685" x2="3.1" y2="0.685" width="0.2032" layer="21" curve="-156.500033"/>
<wire x1="3.1" y1="-0.685" x2="-3.1" y2="-0.685" width="0.2032" layer="21" curve="-154.748326"/>
<circle x="0" y="0" radius="3.15" width="0.1016" layer="51"/>
<smd name="-" x="-2.4" y="0" dx="2.95" dy="1" layer="1"/>
<smd name="+" x="2.4" y="0" dx="2.95" dy="1" layer="1"/>
<text x="-3.2" y="3.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.2" y="-3.85" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_D">
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="-1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="0.95" x2="-3.25" y2="3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="0.95" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-0.95" x2="3.25" y2="-1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="-0.95" width="0.1016" layer="21"/>
<wire x1="2.95" y1="0.95" x2="-2.95" y2="0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.95" y1="-0.95" x2="2.95" y2="-0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.1" y1="2.25" x2="-2.1" y2="-2.2" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="3.1" width="0.1016" layer="51"/>
<smd name="+" x="2.4" y="0" dx="3" dy="1.4" layer="1"/>
<smd name="-" x="-2.4" y="0" dx="3" dy="1.4" layer="1"/>
<text x="-1.75" y="1" size="1.016" layer="25">&gt;NAME</text>
<text x="-1.75" y="-1.975" size="1.016" layer="27">&gt;VALUE</text>
<rectangle x1="-3.65" y1="-0.35" x2="-3.05" y2="0.35" layer="51"/>
<rectangle x1="3.05" y1="-0.35" x2="3.65" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.15" y="2.15"/>
<vertex x="-2.6" y="1.6"/>
<vertex x="-2.9" y="0.9"/>
<vertex x="-3.05" y="0"/>
<vertex x="-2.9" y="-0.95"/>
<vertex x="-2.55" y="-1.65"/>
<vertex x="-2.15" y="-2.15"/>
<vertex x="-2.15" y="2.1"/>
</polygon>
</package>
<package name="CPOL-RADIAL-1000UF-63V">
<wire x1="-3.175" y1="1.905" x2="-4.445" y2="1.905" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="8.001" width="0.2032" layer="21"/>
<pad name="2" x="-3.81" y="0" drill="1.016" diameter="1.6764"/>
<pad name="1" x="3.81" y="0" drill="1.016" diameter="1.651" shape="square"/>
<text x="-2.54" y="8.89" size="0.8128" layer="27">&gt;Value</text>
<text x="-2.54" y="10.16" size="0.8128" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-1000UF-25V">
<wire x1="-1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="5.461" width="0.2032" layer="21"/>
<pad name="2" x="-2.54" y="0" drill="0.7" diameter="1.651"/>
<pad name="1" x="2.54" y="0" drill="0.7" diameter="1.651" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="2.921" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="VISHAY_C">
<wire x1="0" y1="1.27" x2="0" y2="1.905" width="0.254" layer="21"/>
<wire x1="-2.0574" y1="4.2926" x2="-2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="-2.0574" y1="-4.2926" x2="2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="-4.2926" x2="2.0574" y2="4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="4.2926" x2="-2.0574" y2="4.2926" width="0.127" layer="21"/>
<smd name="+" x="0" y="3.048" dx="3.556" dy="1.778" layer="1"/>
<smd name="-" x="0" y="-3.048" dx="3.556" dy="1.778" layer="1"/>
<text x="-1.905" y="4.445" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.905" y="-5.08" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_H13">
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="4" x2="6.75" y2="-4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="1" x2="-6.75" y2="6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="4" x2="6.75" y2="1" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-1" x2="6.75" y2="-4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="-1" width="0.2032" layer="21"/>
<wire x1="-6.55" y1="-1.2" x2="6.45" y2="-1.2" width="0.2032" layer="21" curve="156.692742" cap="flat"/>
<wire x1="-6.55" y1="1.2" x2="6.55" y2="1.2" width="0.2032" layer="21" curve="-156.697982" cap="flat"/>
<wire x1="-5" y1="4.25" x2="-4.95" y2="-4.35" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="6.6" width="0.1016" layer="51"/>
<smd name="-" x="-4.7" y="0" dx="5" dy="1.6" layer="1"/>
<smd name="+" x="4.7" y="0" dx="5" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-7.55" y1="-0.45" x2="-6.6" y2="0.45" layer="51"/>
<rectangle x1="6.6" y1="-0.45" x2="7.55" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-5" y="4.2"/>
<vertex x="-5.75" y="3.15"/>
<vertex x="-6.25" y="2.05"/>
<vertex x="-6.55" y="0.45"/>
<vertex x="-6.55" y="-0.45"/>
<vertex x="-6.35" y="-1.65"/>
<vertex x="-5.75" y="-3.25"/>
<vertex x="-5" y="-4.2"/>
</polygon>
</package>
<package name="EIA6032">
<wire x1="3.2" y1="-1.6" x2="3.2" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="3.2" y2="-1.6" width="0.127" layer="21"/>
<wire x1="3.2" y1="1.6" x2="-2.8" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="1.6" x2="-3.4" y2="1" width="0.127" layer="21"/>
<wire x1="-3.4" y1="1" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<smd name="P$1" x="-2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
<smd name="P$2" x="2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
</package>
<package name="EN_J2">
<description>Type J2 package for SMD supercap PRT-10317 (p# EEC-EN0F204J2)</description>
<wire x1="-2.5" y1="-3.5" x2="2.5" y2="-3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="2.1" y2="3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="-2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="-2.5" y1="3.1" x2="-2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="2.1" y1="3.5" x2="2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="2.5" y1="3.1" x2="2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="-2.5" y1="-3.5" x2="-2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="2.5" y1="-3.5" x2="2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="-2.5908" y1="-2.413" x2="-2.5654" y2="2.4384" width="0.127" layer="21" curve="-91.212564"/>
<wire x1="2.5908" y1="-2.413" x2="2.5654" y2="2.4384" width="0.127" layer="21" curve="86.79344"/>
<wire x1="1.7272" y1="-1.27" x2="1.7272" y2="-2.0828" width="0.127" layer="21"/>
<wire x1="1.3462" y1="-1.6764" x2="2.159" y2="-1.6764" width="0.127" layer="21"/>
<circle x="0" y="0" radius="3.4" width="0.127" layer="51"/>
<smd name="-" x="0" y="2.8" dx="5" dy="2.4" layer="1"/>
<smd name="+" x="0" y="-3.2" dx="5" dy="1.6" layer="1"/>
<text x="-2.28" y="0.66" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.31" y="-1.21" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528-KIT">
<description>&lt;h3&gt;EIA3528-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-0.9" y1="-1.6" x2="-3.1" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-1.6" x2="-3.1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.7" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.55" x2="3.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.1" y1="-1.2" x2="3.1" y2="1.25" width="0.2032" layer="21"/>
<wire x1="3.1" y1="1.25" x2="2.7" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.4" layer="21" style="longdash"/>
<smd name="C" x="-1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<smd name="A" x="1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="EIA3216-KIT">
<description>&lt;h3&gt;EIA3216-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-1" y1="-1.2" x2="-3" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="-1.2" x2="-3" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="3" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="-0.8" x2="3" y2="0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="0.8" x2="2.6" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<smd name="A" x="1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="DIODE-ZENER">
<wire x1="-1.778" y1="0.762" x2="1.778" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.778" y1="0" x2="1.778" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="1.778" y1="-0.762" x2="-1.778" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-1.778" y1="-0.762" x2="-1.778" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.778" y1="0" x2="-1.778" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.778" y1="0" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.778" y1="0" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="1.778" y1="0.762" x2="1.778" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.556" y="0" drill="0.9"/>
<pad name="P$2" x="3.556" y="0" drill="0.9"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.397" y="-0.508" size="0.4064" layer="21">&gt;Value</text>
</package>
<package name="SMB-DIODE">
<description>&lt;b&gt;Diode&lt;/b&gt;&lt;p&gt;
Basic small signal diode good up to 200mA. SMB footprint. Common part #: BAS16</description>
<wire x1="-3.973" y1="1.983" x2="3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="-1.983" x2="-3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-3.973" y1="-1.983" x2="-3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="1.983" x2="3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-2.2606" y1="1.905" x2="2.2606" y2="1.905" width="0.1016" layer="21"/>
<wire x1="-2.2606" y1="-1.905" x2="2.2606" y2="-1.905" width="0.1016" layer="21"/>
<wire x1="-2.261" y1="-1.905" x2="-2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="2.261" y1="-1.905" x2="2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="0.643" y1="1" x2="-0.73" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="0" x2="0.643" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.643" y1="-1" x2="0.643" y2="1" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="1" x2="-0.73" y2="-1" width="0.2032" layer="21"/>
<smd name="C" x="-2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<smd name="A" x="2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<text x="-2.159" y="2.159" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.429" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.794" y1="-1.0922" x2="-2.2606" y2="1.0922" layer="51"/>
<rectangle x1="2.2606" y1="-1.0922" x2="2.794" y2="1.0922" layer="51"/>
</package>
<package name="SOD-323">
<wire x1="-0.9" y1="0.65" x2="-0.5" y2="0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.65" x2="0.9" y2="0.65" width="0.2032" layer="21"/>
<wire x1="-0.9" y1="-0.65" x2="-0.5" y2="-0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="-0.65" x2="0.9" y2="-0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.65" x2="-0.5" y2="-0.65" width="0.2032" layer="21"/>
<smd name="1" x="-1.15" y="0" dx="0.63" dy="0.83" layer="1"/>
<smd name="2" x="1.15" y="0" dx="0.63" dy="0.83" layer="1"/>
<text x="-0.889" y="1.016" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="Q">
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="1.524" x2="-0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.381" y1="-1.524" x2="0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="1.524" x2="-0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.778" x2="1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.778" x2="-1.016" y2="-1.778" width="0.254" layer="94"/>
<text x="2.54" y="1.016" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.159" y="-1.143" size="0.8636" layer="93">1</text>
<text x="1.524" y="-1.143" size="0.8636" layer="93">2</text>
<pin name="2" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="CAP">
<wire x1="0" y1="2.54" x2="0" y2="2.032" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="0.508" width="0.1524" layer="94"/>
<text x="1.524" y="2.921" size="1.778" layer="95">&gt;NAME</text>
<text x="1.524" y="-2.159" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="0.508" x2="2.032" y2="1.016" layer="94"/>
<rectangle x1="-2.032" y1="1.524" x2="2.032" y2="2.032" layer="94"/>
<pin name="1" x="0" y="5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="RESISTOR">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.1524" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.1524" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="CAP_POL">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202" cap="flat"/>
<wire x1="-2.4669" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.376341" cap="flat"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.253" y1="0.668" x2="-1.364" y2="0.795" layer="94"/>
<rectangle x1="-1.872" y1="0.287" x2="-1.745" y2="1.176" layer="94"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="DIODE-ZENER">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.778" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0.762" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CRYSTAL" prefix="Y" uservalue="yes">
<description>&lt;b&gt;Crystals&lt;/b&gt;
Various standard crystals. Proven footprints. Spark Fun Electronics SKU : COM-00534</description>
<gates>
<gate name="G$1" symbol="Q" x="0" y="0"/>
</gates>
<devices>
<device name="HC49UV" package="HC49U-V">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TC38H" package="TC38H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TC26H" package="TC26H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="HC49UP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="HC49US" package="HC49US">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="32-SMD" package="CRYSTAL-32KHZ-SMD">
<connects>
<connect gate="G$1" pin="1" pad="X1"/>
<connect gate="G$1" pin="2" pad="X2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="5X3" package="CRYSTAL-SMD-5X3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EPSONMC146" package="CRYSTAL-32KHZ-SMD_EPSON_MC146">
<connects>
<connect gate="G$1" pin="1" pad="P$2"/>
<connect gate="G$1" pin="2" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="10.5X4.8" package="CRYSTAL-SMD-10.5X4.8-2PIN">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor&lt;/b&gt;
Standard 0603 ceramic capacitor, and 0.1" leaded capacitor.</description>
<gates>
<gate name="G$1" symbol="CAP" x="0" y="0"/>
</gates>
<devices>
<device name="PTH" package="CAP-PTH-SMALL">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CAP-PTH-SMALL2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH3" package="CAP-PTH-LARGE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="GRM43D">
<connects>
<connect gate="G$1" pin="1" pad="A"/>
<connect gate="G$1" pin="2" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603-CAP" package="0603-CAP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402-CAP" package="0402-CAP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CAP-PTH-5MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_" package="AXIAL-5MM">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1210" package="1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="ASMD" package="CTZ3">
<connects>
<connect gate="G$1" pin="1" pad="+"/>
<connect gate="G$1" pin="2" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT" package="CAP-PTH-SMALL-KIT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RESISTOR" prefix="R" uservalue="yes">
<description>&lt;b&gt;Resistor&lt;/b&gt;
Basic schematic elements and footprints for 0603, 1206, and PTH resistors.</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AXIAL-0.3" package="AXIAL-0.3">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2010" package="R2010">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805-RES" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603-RES" package="0603-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402-RES" package="0402-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/6W" package="1/6W-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2512" package="R2512">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/4W" package="AXIAL-0.4">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/2W" package="AXIAL-0.5">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1W" package="AXIAL-0.6">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-2W" package="AXIAL-0.8">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT" package="AXIAL-0.3-KIT">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP_POL" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor Polarized&lt;/b&gt;
These are standard SMD and PTH capacitors. Normally 10uF, 47uF, and 100uF in electrolytic and tantalum varieties. Always verify the external diameter of the through hole cap, it varies with capacity, voltage, and manufacturer. The EIA devices should be standard.</description>
<gates>
<gate name="G$1" symbol="CAP_POL" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="EIA3216">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528" package="EIA3528">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CPOL-RADIAL-100UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CPOL-RADIAL-10UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="7343" package="EIA7343">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="G" package="PANASONIC_G">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="E" package="PANASONIC_E">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="C" package="PANASONIC_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="F80" package="NIPPON_F80">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="D" package="PANASONIC_D">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH3" package="CPOL-RADIAL-1000UF-63V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH4" package="CPOL-RADIAL-1000UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="VISHAY_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="H13" package="PANASONIC_H13">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="6032" package="EIA6032">
<connects>
<connect gate="G$1" pin="+" pad="P$1"/>
<connect gate="G$1" pin="-" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EN_J2" package="EN_J2">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528-KIT" package="EIA3528-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206-KIT" package="EIA3216-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DIODE-ZENER">
<description>Zener Diode
Production Part - 8199
3.4V Zener Voltage</description>
<gates>
<gate name="G$1" symbol="DIODE-ZENER" x="0" y="0"/>
</gates>
<devices>
<device name="PTH" package="DIODE-ZENER">
<connects>
<connect gate="G$1" pin="A" pad="P$2"/>
<connect gate="G$1" pin="C" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMB" package="SMB-DIODE">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-BZT52" package="SOD-323">
<connects>
<connect gate="G$1" pin="A" pad="2"/>
<connect gate="G$1" pin="C" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GNDA">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<wire x1="-1.0922" y1="-0.508" x2="1.0922" y2="-0.508" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="GNDA" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GNDA" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GNDA" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Rebel">
<packages>
<package name="0204/7">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
type 0204, grid 7.5 mm</description>
<wire x1="3.81" y1="0" x2="2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-3.81" y1="0" x2="-2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-2.54" y1="0.762" x2="-2.286" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-0.762" x2="-2.286" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="2.286" y1="1.016" x2="2.54" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="1.016" x2="-1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="0.889" x2="-1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="-1.016" x2="-1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-0.889" x2="-1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.778" y1="0.889" x2="1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="1.778" y1="0.889" x2="-1.778" y2="0.889" width="0.1524" layer="21"/>
<wire x1="1.778" y1="-0.889" x2="1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.778" y1="-0.889" x2="-1.778" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.016" x2="1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.016" x2="1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="2.54" y2="0.762" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="3.81" y="0" drill="0.8128" shape="octagon"/>
<text x="-1.6256" y="-0.4826" size="1.016" layer="25" font="vector" ratio="10">&gt;NAME</text>
<rectangle x1="2.54" y1="-0.254" x2="2.921" y2="0.254" layer="21"/>
<rectangle x1="-2.921" y1="-0.254" x2="-2.54" y2="0.254" layer="21"/>
<text x="-2.54" y="1.2954" size="1.016" layer="27" font="vector" ratio="10">&gt;VALUE</text>
</package>
<package name="0603">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="0" y="0.762" size="1.016" layer="25" font="vector" align="bottom-center">&gt;NAME</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<wire x1="-0.762" y1="0.6731" x2="0.762" y2="0.6731" width="0.127" layer="21"/>
<wire x1="-0.762" y1="-0.6731" x2="0.762" y2="-0.6731" width="0.127" layer="21"/>
</package>
<package name="LED3MM">
<description>&lt;B&gt;LED&lt;/B&gt;&lt;p&gt;
3 mm, round</description>
<wire x1="1.27" y1="-1.016" x2="1.27" y2="1.016" width="0.254" layer="51"/>
<wire x1="-1.524" y1="0" x2="-1.1708" y2="0.9756" width="0.1524" layer="51" curve="-39.80361"/>
<wire x1="-1.524" y1="0" x2="-1.1391" y2="-1.0125" width="0.1524" layer="51" curve="41.633208"/>
<wire x1="0" y1="1.524" x2="1.2401" y2="0.8858" width="0.1524" layer="21" curve="-54.461337"/>
<wire x1="-1.2192" y1="0.9144" x2="0" y2="1.524" width="0.1524" layer="21" curve="-53.130102"/>
<wire x1="0" y1="-1.524" x2="1.203" y2="-0.9356" width="0.1524" layer="21" curve="52.126876"/>
<wire x1="-1.203" y1="-0.9356" x2="0" y2="-1.524" width="0.1524" layer="21" curve="52.126876"/>
<wire x1="-0.635" y1="0" x2="0" y2="0.635" width="0.1524" layer="51" curve="-90"/>
<wire x1="-1.016" y1="0" x2="0" y2="1.016" width="0.1524" layer="51" curve="-90"/>
<wire x1="0" y1="-0.635" x2="0.635" y2="0" width="0.1524" layer="51" curve="90"/>
<wire x1="0" y1="-1.016" x2="1.016" y2="0" width="0.1524" layer="51" curve="90"/>
<wire x1="0" y1="2.032" x2="1.27" y2="1.4732" width="0.254" layer="21" curve="-50.1931"/>
<wire x1="-1.7929" y1="0.9562" x2="0" y2="2.032" width="0.254" layer="21" curve="-61.926949"/>
<wire x1="0" y1="-2.032" x2="1.27" y2="-1.4732" width="0.254" layer="21" curve="49.763"/>
<wire x1="-1.7643" y1="-1.0082" x2="0" y2="-2.032" width="0.254" layer="21" curve="60.255215"/>
<wire x1="-2.032" y1="0" x2="-1.7891" y2="0.9634" width="0.254" layer="51" curve="-28.301701"/>
<wire x1="-2.032" y1="0" x2="-1.7306" y2="-1.065" width="0.254" layer="51" curve="31.60822"/>
<pad name="A" x="-1.27" y="0" drill="0.8128" shape="octagon"/>
<pad name="K" x="1.27" y="0" drill="0.8128" shape="octagon"/>
<text x="-2.286" y="-1.905" size="1.016" layer="25" font="vector" ratio="10" rot="R90">&gt;NAME</text>
<text x="2.921" y="-1.905" size="0.6096" layer="27" font="vector" ratio="10" rot="R90">&gt;VALUE</text>
<wire x1="1.27" y1="1.016" x2="1.27" y2="1.4732" width="0.254" layer="21"/>
<wire x1="1.27" y1="-1.016" x2="1.27" y2="-1.4732" width="0.254" layer="21"/>
</package>
<package name="DIODE-1N4001">
<wire x1="3.175" y1="1.27" x2="1.905" y2="1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.175" y2="0" width="0.254" layer="21"/>
<wire x1="-3.175" y1="0" x2="-3.175" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="3.175" y2="-1.27" width="0.254" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="3.175" y2="0" width="0.254" layer="21"/>
<wire x1="3.175" y1="0" x2="3.175" y2="1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="0" x2="-3.81" y2="0" width="0.254" layer="21"/>
<wire x1="3.175" y1="0" x2="3.81" y2="0" width="0.254" layer="21"/>
<pad name="A" x="-5.08" y="0" drill="1" diameter="1.9812"/>
<pad name="C" x="5.08" y="0" drill="1" diameter="1.9812"/>
<text x="0" y="0" size="1.016" layer="25" font="vector" align="center">&gt;Name</text>
<text x="-2.921" y="1.651" size="0.6096" layer="21" font="vector" ratio="12">&gt;Value</text>
</package>
<package name="DIODE-1N4148">
<wire x1="-1.905" y1="0.762" x2="1.905" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.905" y1="0.762" x2="1.905" y2="0" width="0.2032" layer="21"/>
<wire x1="1.905" y1="0" x2="1.905" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-0.762" x2="-1.905" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-1.905" y1="-0.762" x2="-1.905" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.905" y1="0" x2="-1.905" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.905" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.905" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<pad name="A" x="-3.81" y="0" drill="0.8128"/>
<pad name="C" x="3.81" y="0" drill="0.8128"/>
<text x="0" y="0" size="0.8128" layer="25" font="vector" align="center">&gt;Name</text>
<text x="-2.032" y="1.397" size="0.6096" layer="21" font="vector">&gt;Value</text>
</package>
</packages>
<symbols>
<symbol name="R-EU">
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="LED">
<wire x1="1.27" y1="0" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="-0.762" x2="-3.429" y2="-2.159" width="0.1524" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="-3.302" y2="-3.302" width="0.1524" layer="94"/>
<text x="3.556" y="-4.572" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="5.715" y="-4.572" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="C" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="A" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
<polygon width="0.1524" layer="94">
<vertex x="-3.429" y="-2.159"/>
<vertex x="-3.048" y="-1.27"/>
<vertex x="-2.54" y="-1.778"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="-3.302" y="-3.302"/>
<vertex x="-2.921" y="-2.413"/>
<vertex x="-2.413" y="-2.921"/>
</polygon>
</symbol>
<symbol name="DIODE">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="R-EU_" prefix="R" uservalue="yes">
<description>&lt;B&gt;RESISTOR&lt;/B&gt;, European symbol</description>
<gates>
<gate name="G$1" symbol="R-EU" x="0" y="0"/>
</gates>
<devices>
<device name="0204/7" package="0204/7">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LED" prefix="LED" uservalue="yes">
<description>&lt;b&gt;LED&lt;/b&gt;&lt;p&gt;
</description>
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="3MM" package="LED3MM">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="K"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DIODE" prefix="D" uservalue="yes">
<description>&lt;b&gt;Diode&lt;/b&gt;
These are standard reverse protection diodes and small signal diodes. SMA package can handle up to about 1A. SOD-323 can handle about 200mA. Watch the SOD-323 package when ordering, there are some mfgs out there that are 5-pin packages.</description>
<gates>
<gate name="G$1" symbol="DIODE" x="0" y="0"/>
</gates>
<devices>
<device name="1N4001" package="DIODE-1N4001">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1N4148" package="DIODE-1N4148">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="varistor">
<description>&lt;b&gt;Varistors/Thermistors&lt;/b&gt;&lt;p&gt;
Block, Siemens and generic&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="S10K250">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.524" y1="6.35" x2="1.524" y2="6.35" width="0.1524" layer="21"/>
<wire x1="-1.651" y1="0" x2="-1.651" y2="5.08" width="0.0508" layer="21"/>
<wire x1="1.651" y1="-5.08" x2="1.651" y2="0" width="0.0508" layer="21"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="0" width="0.0508" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.794" y1="-1.905" x2="2.794" y2="3.683" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="1.905" x2="-2.794" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="-2.667" x2="-2.159" y2="-4.953" width="0.1524" layer="51"/>
<wire x1="2.159" y1="2.667" x2="2.159" y2="4.953" width="0.1524" layer="51"/>
<wire x1="-2.794" y1="1.905" x2="-2.159" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.794" y1="-3.683" x2="-2.159" y2="-4.318" width="0.1524" layer="51" curve="90"/>
<wire x1="2.159" y1="4.318" x2="2.794" y2="3.683" width="0.1524" layer="51" curve="-90"/>
<wire x1="2.159" y1="-2.54" x2="2.794" y2="-1.905" width="0.1524" layer="21" curve="90"/>
<wire x1="2.159" y1="-5.715" x2="2.159" y2="2.667" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="-2.667" x2="-2.159" y2="5.715" width="0.1524" layer="21"/>
<wire x1="1.524" y1="-6.35" x2="2.159" y2="-5.715" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.159" y1="-5.715" x2="-1.524" y2="-6.35" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.159" y1="5.715" x2="-1.524" y2="6.35" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.524" y1="6.35" x2="2.159" y2="5.715" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="-6.35" x2="1.524" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="2.159" y1="4.953" x2="2.159" y2="5.715" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="-5.715" x2="-2.159" y2="-4.953" width="0.1524" layer="21"/>
<pad name="1" x="-1.524" y="-3.81" drill="1.016" shape="long"/>
<pad name="2" x="1.524" y="3.81" drill="1.016" shape="long"/>
<text x="-3.175" y="-5.08" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-3.175" y="0.762" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="R-5">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.27" y1="0.635" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0" x2="1.778" y2="0" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="0" x2="-1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="2.54" y="0" drill="0.8128" shape="octagon"/>
<text x="-2.54" y="-2.286" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-1.27" y="1.016" size="1.27" layer="25" ratio="10">&gt;NAME</text>
</package>
<package name="R-7,5">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.54" y1="-1.27" x2="2.54" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.27" x2="-2.54" y2="1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="3.048" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-3.048" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="3.81" y="0" drill="0.8128" shape="octagon"/>
<text x="-2.54" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="CT/CN0402">
<description>&lt;b&gt;EPCOS SMD Varistors, MLV; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.farnell.com/datasheets/49238.pdf</description>
<wire x1="-0.45" y1="0.2" x2="0.45" y2="0.2" width="0.1016" layer="51"/>
<wire x1="0.45" y1="0.2" x2="0.45" y2="-0.2" width="0.1016" layer="51"/>
<wire x1="0.45" y1="-0.2" x2="-0.45" y2="-0.2" width="0.1016" layer="51"/>
<wire x1="-0.45" y1="-0.2" x2="-0.45" y2="0.2" width="0.1016" layer="51"/>
<smd name="1" x="-0.55" y="0" dx="0.6" dy="0.6" layer="1"/>
<smd name="2" x="0.55" y="0" dx="0.6" dy="0.6" layer="1"/>
<text x="-0.75" y="0.5" size="0.8128" layer="25">&gt;NAME</text>
<text x="-0.75" y="-1.25" size="0.8128" layer="27">&gt;VALUE</text>
<rectangle x1="-0.45" y1="-0.2" x2="-0.2" y2="0.2" layer="51"/>
<rectangle x1="0.2" y1="-0.2" x2="0.45" y2="0.2" layer="51" rot="R180"/>
</package>
<package name="CT/CN0603">
<description>&lt;b&gt;EPCOS SMD Varistors, MLV; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.farnell.com/datasheets/49238.pdf</description>
<wire x1="-0.75" y1="0.35" x2="0.75" y2="0.35" width="0.1016" layer="51"/>
<wire x1="0.75" y1="0.35" x2="0.75" y2="-0.35" width="0.1016" layer="51"/>
<wire x1="0.75" y1="-0.35" x2="-0.75" y2="-0.35" width="0.1016" layer="51"/>
<wire x1="-0.75" y1="-0.35" x2="-0.75" y2="0.35" width="0.1016" layer="51"/>
<smd name="1" x="-1" y="0" dx="1" dy="1" layer="1"/>
<smd name="2" x="1" y="0" dx="1" dy="1" layer="1"/>
<text x="-1.5" y="1" size="1.016" layer="25">&gt;NAME</text>
<text x="-1.5" y="-2" size="1.016" layer="27">&gt;VALUE</text>
<rectangle x1="-0.75" y1="-0.35" x2="-0.4" y2="0.35" layer="51"/>
<rectangle x1="0.4" y1="-0.35" x2="0.75" y2="0.35" layer="51" rot="R180"/>
</package>
<package name="CT/CN0805">
<description>&lt;b&gt;EPCOS SMD Varistors, MLV; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.farnell.com/datasheets/49238.pdf</description>
<wire x1="-0.95" y1="0.6" x2="0.95" y2="0.6" width="0.1016" layer="51"/>
<wire x1="0.95" y1="0.6" x2="0.95" y2="-0.6" width="0.1016" layer="51"/>
<wire x1="0.95" y1="-0.6" x2="-0.95" y2="-0.6" width="0.1016" layer="51"/>
<wire x1="-0.95" y1="-0.6" x2="-0.95" y2="0.6" width="0.1016" layer="51"/>
<smd name="1" x="-1.1" y="0" dx="1.2" dy="1.4" layer="1"/>
<smd name="2" x="1.1" y="0" dx="1.2" dy="1.4" layer="1"/>
<text x="-1.5" y="1" size="1.016" layer="25">&gt;NAME</text>
<text x="-1.5" y="-2" size="1.016" layer="27">&gt;VALUE</text>
<rectangle x1="-0.95" y1="-0.6" x2="-0.4" y2="0.6" layer="51"/>
<rectangle x1="0.4" y1="-0.6" x2="0.95" y2="0.6" layer="51" rot="R180"/>
</package>
<package name="CT/CN1206">
<description>&lt;b&gt;EPCOS SMD Varistors, MLV; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.farnell.com/datasheets/49238.pdf</description>
<wire x1="-1.65" y1="0.75" x2="1.65" y2="0.75" width="0.1016" layer="51"/>
<wire x1="1.65" y1="0.75" x2="1.65" y2="-0.75" width="0.1016" layer="51"/>
<wire x1="1.65" y1="-0.75" x2="-1.65" y2="-0.75" width="0.1016" layer="51"/>
<wire x1="-1.65" y1="-0.75" x2="-1.65" y2="0.75" width="0.1016" layer="51"/>
<smd name="1" x="-1.65" y="0" dx="1.2" dy="1.8" layer="1"/>
<smd name="2" x="1.65" y="0" dx="1.2" dy="1.8" layer="1"/>
<text x="-2" y="1" size="1.27" layer="25">&gt;NAME</text>
<text x="-2" y="-2.5" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.65" y1="-0.75" x2="-0.95" y2="0.75" layer="51"/>
<rectangle x1="0.95" y1="-0.75" x2="1.65" y2="0.75" layer="51" rot="R180"/>
</package>
<package name="CT/CN1210">
<description>&lt;b&gt;EPCOS SMD Varistors, MLV; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.farnell.com/datasheets/49238.pdf</description>
<wire x1="-1.65" y1="1.25" x2="1.65" y2="1.25" width="0.1016" layer="51"/>
<wire x1="1.65" y1="1.25" x2="1.65" y2="-1.25" width="0.1016" layer="51"/>
<wire x1="1.65" y1="-1.25" x2="-1.65" y2="-1.25" width="0.1016" layer="51"/>
<wire x1="-1.65" y1="-1.25" x2="-1.65" y2="1.25" width="0.1016" layer="51"/>
<smd name="1" x="-1.65" y="0" dx="1.2" dy="2.8" layer="1"/>
<smd name="2" x="1.65" y="0" dx="1.2" dy="2.8" layer="1"/>
<text x="-2" y="1.5" size="1.27" layer="25">&gt;NAME</text>
<text x="-2" y="-3" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.65" y1="-1.25" x2="-0.95" y2="1.25" layer="51"/>
<rectangle x1="0.95" y1="-1.25" x2="1.65" y2="1.25" layer="51" rot="R180"/>
</package>
<package name="CT/CN1812">
<description>&lt;b&gt;EPCOS SMD Varistors, MLV; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.farnell.com/datasheets/49238.pdf</description>
<wire x1="-2.35" y1="1.55" x2="2.35" y2="1.55" width="0.1016" layer="51"/>
<wire x1="2.35" y1="1.55" x2="2.35" y2="-1.55" width="0.1016" layer="51"/>
<wire x1="2.35" y1="-1.55" x2="-2.35" y2="-1.55" width="0.1016" layer="51"/>
<wire x1="-2.35" y1="-1.55" x2="-2.35" y2="1.55" width="0.1016" layer="51"/>
<smd name="1" x="-2.25" y="0" dx="1.5" dy="3.6" layer="1"/>
<smd name="2" x="2.25" y="0" dx="1.5" dy="3.6" layer="1"/>
<text x="-2.5" y="2.5" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.5" y="-3.5" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.35" y1="-1.55" x2="-1.4" y2="1.55" layer="51"/>
<rectangle x1="1.4" y1="-1.55" x2="2.35" y2="1.55" layer="51" rot="R180"/>
</package>
<package name="CT/CN2220">
<description>&lt;b&gt;EPCOS SMD Varistors, MLV; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.farnell.com/datasheets/49238.pdf</description>
<wire x1="-2.95" y1="2.45" x2="2.95" y2="2.45" width="0.1016" layer="51"/>
<wire x1="2.95" y1="2.45" x2="2.95" y2="-2.45" width="0.1016" layer="51"/>
<wire x1="2.95" y1="-2.45" x2="-2.95" y2="-2.45" width="0.1016" layer="51"/>
<wire x1="-2.95" y1="-2.45" x2="-2.95" y2="2.45" width="0.1016" layer="51"/>
<smd name="1" x="-2.85" y="0" dx="1.5" dy="5.5" layer="1"/>
<smd name="2" x="2.85" y="0" dx="1.5" dy="5.5" layer="1"/>
<text x="-3.5" y="3" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.5" y="-4.5" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.95" y1="-2.45" x2="-2.01" y2="2.44" layer="51"/>
<rectangle x1="2.01" y1="-2.44" x2="2.95" y2="2.45" layer="51" rot="R180"/>
</package>
<package name="S05K11">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-0.762" y1="3.683" x2="0.762" y2="3.683" width="0.1524" layer="21"/>
<wire x1="1.778" y1="2.667" x2="1.778" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="2.667" x2="-1.778" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="-3.683" x2="0.762" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-1.143" x2="-1.016" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.016" y1="-2.032" x2="1.016" y2="1.143" width="0.0508" layer="21"/>
<wire x1="0.762" y1="-3.683" x2="1.778" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.778" y1="2.667" x2="-0.762" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.778" y1="-2.667" x2="-0.762" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="0.762" y1="3.683" x2="1.778" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="0.762" y1="0" x2="0.762" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-0.762" y1="-1.143" x2="-0.762" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-0.635" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="0.635" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.032" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.302" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K17">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-0.889" y1="3.683" x2="0.889" y2="3.683" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.667" x2="1.905" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.667" x2="-1.905" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-0.889" y1="-3.683" x2="0.889" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-1.143" x2="-1.143" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.143" y1="-2.032" x2="1.143" y2="1.143" width="0.0508" layer="21"/>
<wire x1="0.889" y1="-3.683" x2="1.905" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.905" y1="2.667" x2="-0.889" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.905" y1="-2.667" x2="-0.889" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="0.889" y1="3.683" x2="1.905" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="0.889" y1="0" x2="0.889" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-0.889" y1="-1.143" x2="-0.889" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-0.762" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="0.762" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.286" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.556" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K175">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.143" y1="3.683" x2="1.143" y2="3.683" width="0.1524" layer="21"/>
<wire x1="2.159" y1="2.667" x2="2.159" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="2.667" x2="-2.159" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-3.683" x2="1.143" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="-1.143" x2="-1.397" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.27" y1="-2.032" x2="1.27" y2="1.143" width="0.0508" layer="21"/>
<wire x1="1.143" y1="-3.683" x2="2.159" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.159" y1="2.667" x2="-1.143" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.159" y1="-2.667" x2="-1.143" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="1.143" y1="3.683" x2="2.159" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.016" y1="0" x2="1.016" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-1.143" y1="-1.143" x2="-1.143" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-1.016" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.016" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.54" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.81" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K230">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.397" y1="3.683" x2="1.397" y2="3.683" width="0.1524" layer="21"/>
<wire x1="2.413" y1="2.667" x2="2.413" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="2.667" x2="-2.413" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="-3.683" x2="1.397" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-1.143" x2="-1.524" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.524" y1="-2.032" x2="1.524" y2="1.143" width="0.0508" layer="21"/>
<wire x1="1.397" y1="-3.683" x2="2.413" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.413" y1="2.667" x2="-1.397" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.413" y1="-2.667" x2="-1.397" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="1.397" y1="3.683" x2="2.413" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.27" y1="0" x2="1.27" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-1.27" y1="-1.143" x2="-1.27" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-1.27" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.27" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.794" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.064" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K250">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.524" y1="3.683" x2="1.524" y2="3.683" width="0.1524" layer="21"/>
<wire x1="2.54" y1="2.667" x2="2.54" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="2.667" x2="-2.54" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-3.683" x2="1.524" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.651" y1="-1.143" x2="-1.651" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.651" y1="-2.032" x2="1.651" y2="1.143" width="0.0508" layer="21"/>
<wire x1="1.524" y1="-3.683" x2="2.54" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.54" y1="2.667" x2="-1.524" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-2.667" x2="-1.524" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="1.524" y1="3.683" x2="2.54" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.397" y1="0" x2="1.397" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-1.397" y1="-1.143" x2="-1.397" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-1.397" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.397" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.921" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.191" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K275">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.651" y1="3.683" x2="1.651" y2="3.683" width="0.1524" layer="21"/>
<wire x1="2.667" y1="2.667" x2="2.667" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.667" y1="2.667" x2="-2.667" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.651" y1="-3.683" x2="1.651" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-1.143" x2="-1.778" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.778" y1="-2.032" x2="1.778" y2="1.143" width="0.0508" layer="21"/>
<wire x1="1.651" y1="-3.683" x2="2.667" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.667" y1="2.667" x2="-1.651" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.667" y1="-2.667" x2="-1.651" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="1.651" y1="3.683" x2="2.667" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.524" y1="0" x2="1.524" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-1.524" y1="-1.143" x2="-1.524" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-1.524" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.524" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.175" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.318" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K300">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.651" y1="3.683" x2="1.651" y2="3.683" width="0.1524" layer="21"/>
<wire x1="2.667" y1="2.667" x2="2.667" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.667" y1="2.667" x2="-2.667" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.651" y1="-3.683" x2="1.651" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-1.143" x2="-1.778" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.778" y1="-2.032" x2="1.778" y2="1.143" width="0.0508" layer="21"/>
<wire x1="1.651" y1="-3.683" x2="2.667" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.667" y1="2.667" x2="-1.651" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.667" y1="-2.667" x2="-1.651" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="1.651" y1="3.683" x2="2.667" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.524" y1="0" x2="1.524" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-1.524" y1="-1.143" x2="-1.524" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-1.524" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.524" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.175" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.318" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K385">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.159" y1="3.683" x2="2.159" y2="3.683" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.667" x2="3.175" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.667" x2="-3.175" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="-3.683" x2="2.159" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="-1.143" x2="-2.286" y2="1.905" width="0.0508" layer="21"/>
<wire x1="2.286" y1="-1.905" x2="2.286" y2="1.143" width="0.0508" layer="21"/>
<wire x1="2.159" y1="-3.683" x2="3.175" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-3.175" y1="2.667" x2="-2.159" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.175" y1="-2.667" x2="-2.159" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="2.159" y1="3.683" x2="3.175" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.905" y1="-1.143" x2="-1.905" y2="0" width="0.0508" layer="21"/>
<wire x1="1.905" y1="0" x2="1.905" y2="1.143" width="0.0508" layer="21"/>
<pad name="1" x="-1.905" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.905" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.556" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.826" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K40">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.143" y1="3.683" x2="1.143" y2="3.683" width="0.1524" layer="21"/>
<wire x1="2.159" y1="2.667" x2="2.159" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="2.667" x2="-2.159" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-3.683" x2="1.143" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="2.032" width="0.0508" layer="21"/>
<wire x1="1.27" y1="-2.032" x2="1.27" y2="1.27" width="0.0508" layer="21"/>
<wire x1="1.143" y1="-3.683" x2="2.159" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.159" y1="2.667" x2="-1.143" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.159" y1="-2.667" x2="-1.143" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="1.143" y1="3.683" x2="2.159" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.016" y1="-1.27" x2="-1.016" y2="0" width="0.0508" layer="21"/>
<wire x1="1.016" y1="0" x2="1.016" y2="1.27" width="0.0508" layer="21"/>
<pad name="1" x="-0.889" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="0.889" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.54" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.81" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K420">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.286" y1="3.683" x2="2.286" y2="3.683" width="0.1524" layer="21"/>
<wire x1="3.302" y1="2.667" x2="3.302" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="2.667" x2="-3.302" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="-3.683" x2="2.286" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.143" x2="-2.54" y2="1.905" width="0.0508" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="1.143" width="0.0508" layer="21"/>
<wire x1="2.286" y1="-3.683" x2="3.302" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-3.302" y1="2.667" x2="-2.286" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.302" y1="-2.667" x2="-2.286" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="2.286" y1="3.683" x2="3.302" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.159" y1="0" x2="2.159" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-2.159" y1="-1.143" x2="-2.159" y2="0" width="0.0508" layer="21"/>
<pad name="1" x="-2.159" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="2.159" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.81" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.953" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K440">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.413" y1="3.683" x2="2.413" y2="3.683" width="0.1524" layer="21"/>
<wire x1="3.429" y1="2.667" x2="3.429" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-3.429" y1="2.667" x2="-3.429" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="-3.683" x2="2.413" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="-1.143" x2="-2.032" y2="0" width="0.0508" layer="21"/>
<wire x1="2.032" y1="0" x2="2.032" y2="1.143" width="0.0508" layer="21"/>
<wire x1="2.413" y1="-3.683" x2="3.429" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-3.429" y1="2.667" x2="-2.413" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.429" y1="-2.667" x2="-2.413" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="2.413" y1="3.683" x2="3.429" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.286" y1="-1.905" x2="2.286" y2="1.143" width="0.0508" layer="21"/>
<wire x1="-2.286" y1="-1.143" x2="-2.286" y2="1.905" width="0.0508" layer="21"/>
<pad name="1" x="-2.286" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="2.286" y="2.54" drill="0.9144" shape="long"/>
<text x="-4.064" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="5.334" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S05K460">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.54" y1="3.683" x2="2.54" y2="3.683" width="0.1524" layer="21"/>
<wire x1="3.556" y1="2.667" x2="3.556" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-3.556" y1="2.667" x2="-3.556" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-3.683" x2="2.54" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="0.889" x2="-2.286" y2="1.905" width="0.0508" layer="21"/>
<wire x1="2.286" y1="-1.905" x2="2.286" y2="-0.889" width="0.0508" layer="21"/>
<wire x1="2.54" y1="-3.683" x2="3.556" y2="-2.667" width="0.1524" layer="21" curve="90"/>
<wire x1="-3.556" y1="2.667" x2="-2.54" y2="3.683" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.556" y1="-2.667" x2="-2.54" y2="-3.683" width="0.1524" layer="21" curve="90"/>
<wire x1="2.54" y1="3.683" x2="3.556" y2="2.667" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-1.143" x2="-2.54" y2="1.905" width="0.0508" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="1.143" width="0.0508" layer="21"/>
<pad name="1" x="-2.413" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="2.413" y="2.54" drill="0.9144" shape="long"/>
<text x="-4.064" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="5.334" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K11">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-0.508" y1="4.572" x2="0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.397" x2="-0.635" y2="2.54" width="0.0508" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="0.635" y2="1.397" width="0.0508" layer="21"/>
<wire x1="0.381" y1="-1.905" x2="0.381" y2="0" width="0.0508" layer="21"/>
<wire x1="-0.381" y1="0" x2="-0.381" y2="1.905" width="0.0508" layer="21"/>
<wire x1="1.778" y1="-0.635" x2="1.778" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="0.635" x2="-1.778" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-1.524" x2="-1.143" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="1.143" y1="1.524" x2="1.143" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-1.778" y1="0.635" x2="-1.143" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.778" y1="-2.413" x2="-1.143" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="1.143" y1="3.048" x2="1.778" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="1.143" y1="-1.27" x2="1.778" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="1.143" y1="-3.937" x2="1.143" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-1.524" x2="-1.143" y2="3.937" width="0.1524" layer="21"/>
<wire x1="0.508" y1="-4.572" x2="1.143" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.143" y1="-3.937" x2="-0.508" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.143" y1="3.937" x2="-0.508" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="0.508" y1="4.572" x2="1.143" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.508" y1="-4.572" x2="0.508" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="1.143" y1="3.556" x2="1.143" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-3.937" x2="-1.143" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-0.635" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="0.635" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.032" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.429" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K17">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-0.635" y1="4.572" x2="0.635" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="-1.397" x2="-0.762" y2="2.54" width="0.0508" layer="21"/>
<wire x1="0.762" y1="-2.54" x2="0.762" y2="1.397" width="0.0508" layer="21"/>
<wire x1="0.508" y1="-2.54" x2="0.508" y2="0" width="0.0508" layer="21"/>
<wire x1="-0.508" y1="0" x2="-0.508" y2="2.54" width="0.0508" layer="21"/>
<wire x1="1.905" y1="-0.635" x2="1.905" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="0.635" x2="-1.905" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.524" x2="-1.27" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="1.27" y1="1.524" x2="1.27" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-1.905" y1="0.635" x2="-1.27" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.905" y1="-2.413" x2="-1.27" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="1.27" y1="3.048" x2="1.905" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="1.27" y1="-1.27" x2="1.905" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="1.27" y1="-3.937" x2="1.27" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.524" x2="-1.27" y2="3.937" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-4.572" x2="1.27" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.27" y1="-3.937" x2="-0.635" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.27" y1="3.937" x2="-0.635" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="0.635" y1="4.572" x2="1.27" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.635" y1="-4.572" x2="0.635" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="1.27" y1="3.556" x2="1.27" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-3.937" x2="-1.27" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-0.762" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="0.762" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.286" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.556" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K175">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-0.889" y1="4.572" x2="0.889" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-1.397" x2="-1.016" y2="2.54" width="0.0508" layer="21"/>
<wire x1="1.016" y1="-2.54" x2="1.016" y2="1.397" width="0.0508" layer="21"/>
<wire x1="0.762" y1="-2.54" x2="0.762" y2="0" width="0.0508" layer="21"/>
<wire x1="-0.762" y1="0" x2="-0.762" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.159" y1="-0.635" x2="2.159" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="0.635" x2="-2.159" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-1.524" x2="-1.524" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="1.524" y1="1.524" x2="1.524" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-2.159" y1="0.635" x2="-1.524" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.159" y1="-2.413" x2="-1.524" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="1.524" y1="3.048" x2="2.159" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="1.524" y1="-1.27" x2="2.159" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="1.524" y1="-3.937" x2="1.524" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-1.524" x2="-1.524" y2="3.937" width="0.1524" layer="21"/>
<wire x1="0.889" y1="-4.572" x2="1.524" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.524" y1="-3.937" x2="-0.889" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.524" y1="3.937" x2="-0.889" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="0.889" y1="4.572" x2="1.524" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.889" y1="-4.572" x2="0.889" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="1.524" y1="3.556" x2="1.524" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-3.937" x2="-1.524" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-1.016" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.016" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.54" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.81" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K230">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.143" y1="4.572" x2="1.143" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.397" x2="-1.27" y2="2.54" width="0.0508" layer="21"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="1.397" width="0.0508" layer="21"/>
<wire x1="1.016" y1="-2.54" x2="1.016" y2="0" width="0.0508" layer="21"/>
<wire x1="-1.016" y1="0" x2="-1.016" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.413" y1="-0.635" x2="2.413" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="0.635" x2="-2.413" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-1.524" x2="-1.778" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="1.778" y1="1.524" x2="1.778" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-2.413" y1="0.635" x2="-1.778" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.413" y1="-2.413" x2="-1.778" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="1.778" y1="3.048" x2="2.413" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="1.778" y1="-1.27" x2="2.413" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="1.778" y1="-3.937" x2="1.778" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-1.524" x2="-1.778" y2="3.937" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-4.572" x2="1.778" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.778" y1="-3.937" x2="-1.143" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.778" y1="3.937" x2="-1.143" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.143" y1="4.572" x2="1.778" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.143" y1="-4.572" x2="1.143" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="1.778" y1="3.556" x2="1.778" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-3.937" x2="-1.778" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.27" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.794" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.064" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K250">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.27" y1="4.572" x2="1.27" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="-1.397" x2="-1.397" y2="2.54" width="0.0508" layer="21"/>
<wire x1="1.397" y1="-2.54" x2="1.397" y2="1.397" width="0.0508" layer="21"/>
<wire x1="1.143" y1="-2.54" x2="1.143" y2="0" width="0.0508" layer="21"/>
<wire x1="-1.143" y1="0" x2="-1.143" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.524" x2="-1.905" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="1.905" y1="1.524" x2="1.905" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-2.54" y1="0.635" x2="-1.905" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-2.413" x2="-1.905" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="1.905" y1="3.048" x2="2.54" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="1.905" y1="-1.27" x2="2.54" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="1.905" y1="-3.937" x2="1.905" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.524" x2="-1.905" y2="3.937" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-4.572" x2="1.905" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.905" y1="-3.937" x2="-1.27" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.905" y1="3.937" x2="-1.27" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.27" y1="4.572" x2="1.905" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.27" y1="-4.572" x2="1.27" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="1.905" y1="3.556" x2="1.905" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-3.937" x2="-1.905" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-1.397" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.397" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.921" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.191" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K275">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.397" y1="4.572" x2="1.397" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-1.397" x2="-1.524" y2="2.54" width="0.0508" layer="21"/>
<wire x1="1.524" y1="-2.54" x2="1.524" y2="1.397" width="0.0508" layer="21"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="0" width="0.0508" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.667" y1="-0.635" x2="2.667" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-2.667" y1="0.635" x2="-2.667" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="-1.524" x2="-2.032" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="2.032" y1="1.524" x2="2.032" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-2.667" y1="0.635" x2="-2.032" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.667" y1="-2.413" x2="-2.032" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="2.032" y1="3.048" x2="2.667" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="2.032" y1="-1.27" x2="2.667" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="2.032" y1="-3.937" x2="2.032" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="-1.524" x2="-2.032" y2="3.937" width="0.1524" layer="21"/>
<wire x1="1.397" y1="-4.572" x2="2.032" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.032" y1="-3.937" x2="-1.397" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.032" y1="3.937" x2="-1.397" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.397" y1="4.572" x2="2.032" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.397" y1="-4.572" x2="1.397" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="2.032" y1="3.556" x2="2.032" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="-3.937" x2="-2.032" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-1.524" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.524" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.048" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.318" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K385">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-1.905" y1="4.572" x2="1.905" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="-1.397" x2="-2.032" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.032" y1="-2.54" x2="2.032" y2="1.397" width="0.0508" layer="21"/>
<wire x1="1.778" y1="-2.54" x2="1.778" y2="0" width="0.0508" layer="21"/>
<wire x1="-1.778" y1="0" x2="-1.778" y2="2.54" width="0.0508" layer="21"/>
<wire x1="3.175" y1="-0.635" x2="3.175" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="0.635" x2="-3.175" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.524" x2="-2.54" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="2.54" y1="1.524" x2="2.54" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-3.175" y1="0.635" x2="-2.54" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.175" y1="-2.413" x2="-2.54" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="2.54" y1="3.048" x2="3.175" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="2.54" y1="-1.27" x2="3.175" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="2.54" y1="-3.937" x2="2.54" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.524" x2="-2.54" y2="3.937" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-4.572" x2="2.54" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.54" y1="-3.937" x2="-1.905" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.54" y1="3.937" x2="-1.905" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.905" y1="4.572" x2="2.54" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.905" y1="-4.572" x2="1.905" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="2.54" y1="3.556" x2="2.54" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-3.937" x2="-2.54" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-1.905" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="1.905" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.556" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.826" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K40">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-0.762" y1="4.572" x2="0.762" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-0.889" y1="-1.397" x2="-0.889" y2="2.54" width="0.0508" layer="21"/>
<wire x1="0.889" y1="-2.54" x2="0.889" y2="1.397" width="0.0508" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="0.635" y2="0" width="0.0508" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.032" y1="-0.635" x2="2.032" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="0.635" x2="-2.032" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="-1.524" x2="-1.397" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="1.397" y1="1.524" x2="1.397" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-2.032" y1="0.635" x2="-1.397" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.032" y1="-2.413" x2="-1.397" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="1.397" y1="3.048" x2="2.032" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="1.397" y1="-1.27" x2="2.032" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="1.397" y1="-3.937" x2="1.397" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="-1.524" x2="-1.397" y2="3.937" width="0.1524" layer="21"/>
<wire x1="0.762" y1="-4.572" x2="1.397" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.397" y1="-3.937" x2="-0.762" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.397" y1="3.937" x2="-0.762" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="0.762" y1="4.572" x2="1.397" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.762" y1="-4.572" x2="0.762" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="1.397" y1="3.556" x2="1.397" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="-3.937" x2="-1.397" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-0.889" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="0.889" y="2.54" drill="0.9144" shape="long"/>
<text x="-2.413" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.683" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K420">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.032" y1="4.572" x2="2.032" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="-1.397" x2="-2.159" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.159" y1="-2.54" x2="2.159" y2="1.397" width="0.0508" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="1.905" y2="0" width="0.0508" layer="21"/>
<wire x1="-1.905" y1="0" x2="-1.905" y2="2.54" width="0.0508" layer="21"/>
<wire x1="3.302" y1="-0.635" x2="3.302" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="0.635" x2="-3.302" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-2.667" y1="-1.524" x2="-2.667" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="2.667" y1="1.524" x2="2.667" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-3.302" y1="0.635" x2="-2.667" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.302" y1="-2.413" x2="-2.667" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="2.667" y1="3.048" x2="3.302" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="2.667" y1="-1.27" x2="3.302" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="2.667" y1="-3.937" x2="2.667" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-2.667" y1="-1.524" x2="-2.667" y2="3.937" width="0.1524" layer="21"/>
<wire x1="2.032" y1="-4.572" x2="2.667" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.667" y1="-3.937" x2="-2.032" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.667" y1="3.937" x2="-2.032" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.032" y1="4.572" x2="2.667" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.032" y1="-4.572" x2="2.032" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="2.667" y1="3.556" x2="2.667" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-2.667" y1="-3.937" x2="-2.667" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-2.159" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="2.159" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.683" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.953" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K440">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.159" y1="4.572" x2="2.159" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="-1.397" x2="-2.286" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.286" y1="-2.54" x2="2.286" y2="1.397" width="0.0508" layer="21"/>
<wire x1="2.032" y1="-2.54" x2="2.032" y2="0" width="0.0508" layer="21"/>
<wire x1="-2.032" y1="0" x2="-2.032" y2="2.54" width="0.0508" layer="21"/>
<wire x1="3.429" y1="-0.635" x2="3.429" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-3.429" y1="0.635" x2="-3.429" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="-1.524" x2="-2.794" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="2.794" y1="1.524" x2="2.794" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-3.429" y1="0.635" x2="-2.794" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.429" y1="-2.413" x2="-2.794" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="2.794" y1="3.048" x2="3.429" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="2.794" y1="-1.27" x2="3.429" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="2.794" y1="-3.937" x2="2.794" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="-1.524" x2="-2.794" y2="3.937" width="0.1524" layer="21"/>
<wire x1="2.159" y1="-4.572" x2="2.794" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.794" y1="-3.937" x2="-2.159" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.794" y1="3.937" x2="-2.159" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.159" y1="4.572" x2="2.794" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.159" y1="-4.572" x2="2.159" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="2.794" y1="3.556" x2="2.794" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="-3.937" x2="-2.794" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-2.286" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="2.286" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.81" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="5.08" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="S07K460">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<wire x1="-2.286" y1="4.572" x2="2.286" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="-1.397" x2="-2.413" y2="2.54" width="0.0508" layer="21"/>
<wire x1="2.413" y1="-2.54" x2="2.413" y2="1.397" width="0.0508" layer="21"/>
<wire x1="2.159" y1="-2.54" x2="2.159" y2="0" width="0.0508" layer="21"/>
<wire x1="-2.159" y1="0" x2="-2.159" y2="2.54" width="0.0508" layer="21"/>
<wire x1="3.556" y1="-0.635" x2="3.556" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-3.556" y1="0.635" x2="-3.556" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="-1.524" x2="-2.921" y2="-3.556" width="0.1524" layer="51"/>
<wire x1="2.921" y1="1.524" x2="2.921" y2="3.556" width="0.1524" layer="51"/>
<wire x1="-3.556" y1="0.635" x2="-2.921" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.556" y1="-2.413" x2="-2.921" y2="-3.048" width="0.1524" layer="51" curve="90"/>
<wire x1="2.921" y1="3.048" x2="3.556" y2="2.413" width="0.1524" layer="51" curve="-90"/>
<wire x1="2.921" y1="-1.27" x2="3.556" y2="-0.635" width="0.1524" layer="21" curve="90"/>
<wire x1="2.921" y1="-3.937" x2="2.921" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="-1.524" x2="-2.921" y2="3.937" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-4.572" x2="2.921" y2="-3.937" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.921" y1="-3.937" x2="-2.286" y2="-4.572" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.921" y1="3.937" x2="-2.286" y2="4.572" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.286" y1="4.572" x2="2.921" y2="3.937" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.286" y1="-4.572" x2="2.286" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="2.921" y1="3.556" x2="2.921" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="-3.937" x2="-2.921" y2="-3.556" width="0.1524" layer="21"/>
<pad name="1" x="-2.413" y="-2.54" drill="0.9144" shape="long"/>
<pad name="2" x="2.413" y="2.54" drill="0.9144" shape="long"/>
<text x="-3.937" y="-4.064" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="5.207" y="-4.064" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="CU3225K">
<description>&lt;b&gt;SMD Varistors Monolithic; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.epcos.com .. 01430148.pdf</description>
<wire x1="-3.5" y1="3.05" x2="3.5" y2="3.05" width="0.2032" layer="21"/>
<wire x1="3.5" y1="3.05" x2="3.5" y2="-3.05" width="0.2032" layer="51"/>
<wire x1="3.5" y1="-3.05" x2="-3.5" y2="-3.05" width="0.2032" layer="21"/>
<wire x1="-3.5" y1="-3.05" x2="-3.5" y2="3.05" width="0.2032" layer="51"/>
<wire x1="-3.5" y1="-3.05" x2="-3.5" y2="-1.95" width="0.2032" layer="21"/>
<wire x1="3.5" y1="-1.95" x2="3.5" y2="-3.05" width="0.2032" layer="21"/>
<wire x1="3.5" y1="3.05" x2="3.5" y2="1.95" width="0.2032" layer="21"/>
<wire x1="-3.5" y1="1.95" x2="-3.5" y2="3.05" width="0.2032" layer="21"/>
<smd name="1" x="-3.65" y="0" dx="2.8" dy="3.5" layer="1"/>
<smd name="2" x="3.65" y="0" dx="2.8" dy="3.5" layer="1"/>
<text x="-3.5" y="3.5" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.5" y="-5" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-4" y1="-1.5" x2="-3.6" y2="1.5" layer="51"/>
<rectangle x1="3.6" y1="-1.5" x2="4" y2="1.5" layer="51" rot="R180"/>
</package>
<package name="CU4032K">
<description>&lt;b&gt;SMD Varistors Monolithic; Standard Series&lt;/b&gt;&lt;p&gt;
Source: www.epcos.com .. 01430148.pdf</description>
<wire x1="-4.55" y1="3.9" x2="4.55" y2="3.9" width="0.2032" layer="21"/>
<wire x1="4.55" y1="3.9" x2="4.55" y2="-3.9" width="0.2032" layer="51"/>
<wire x1="4.55" y1="-3.9" x2="-4.55" y2="-3.9" width="0.2032" layer="21"/>
<wire x1="-4.55" y1="-3.9" x2="-4.55" y2="3.9" width="0.2032" layer="51"/>
<wire x1="-4.55" y1="-3.9" x2="-4.55" y2="-1.95" width="0.2032" layer="21"/>
<wire x1="4.55" y1="-1.95" x2="4.55" y2="-3.9" width="0.2032" layer="21"/>
<wire x1="4.55" y1="3.9" x2="4.55" y2="1.95" width="0.2032" layer="21"/>
<wire x1="-4.55" y1="1.95" x2="-4.55" y2="3.9" width="0.2032" layer="21"/>
<smd name="1" x="-4.65" y="0" dx="2.8" dy="3.5" layer="1"/>
<smd name="2" x="4.65" y="0" dx="2.8" dy="3.5" layer="1"/>
<text x="-4.55" y="4.35" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.55" y="-5.85" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-5.05" y1="-1.5" x2="-4.65" y2="1.5" layer="51"/>
<rectangle x1="4.65" y1="-1.5" x2="5.05" y2="1.5" layer="51" rot="R180"/>
</package>
</packages>
<symbols>
<symbol name="VDR">
<wire x1="-3.81" y1="-0.889" x2="3.81" y2="-0.889" width="0.254" layer="94"/>
<wire x1="3.81" y1="-0.889" x2="3.81" y2="0" width="0.254" layer="94"/>
<wire x1="3.81" y1="0.889" x2="-3.81" y2="0.889" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-0.889" x2="-3.81" y2="0" width="0.254" layer="94"/>
<wire x1="3.81" y1="0" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="3.81" y1="0" x2="3.81" y2="0.889" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-3.81" y2="0" width="0.1524" layer="94"/>
<wire x1="-3.81" y1="0" x2="-3.81" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="-2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-3.81" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-1.1938" y1="-2.1082" x2="-1.1938" y2="-3.4798" width="0.1524" layer="94"/>
<wire x1="-0.9398" y1="-3.7338" x2="-1.1938" y2="-3.4798" width="0.1524" layer="94"/>
<wire x1="-0.9398" y1="-3.7338" x2="-0.381" y2="-3.7338" width="0.1524" layer="94"/>
<wire x1="-0.127" y1="-3.4798" x2="-0.381" y2="-3.7338" width="0.1524" layer="94"/>
<wire x1="-0.127" y1="-3.4798" x2="-0.127" y2="-2.1082" width="0.1524" layer="94"/>
<wire x1="5.715" y1="5.08" x2="5.715" y2="2.54" width="0.1524" layer="94"/>
<wire x1="5.715" y1="2.54" x2="6.096" y2="3.81" width="0.1524" layer="94"/>
<wire x1="6.096" y1="3.81" x2="5.334" y2="3.81" width="0.1524" layer="94"/>
<wire x1="5.334" y1="3.81" x2="5.715" y2="2.54" width="0.1524" layer="94"/>
<wire x1="4.445" y1="2.54" x2="4.445" y2="5.08" width="0.1524" layer="94"/>
<wire x1="4.445" y1="5.08" x2="4.826" y2="3.81" width="0.1524" layer="94"/>
<wire x1="4.826" y1="3.81" x2="4.064" y2="3.81" width="0.1524" layer="94"/>
<wire x1="4.064" y1="3.81" x2="4.445" y2="5.08" width="0.1524" layer="94"/>
<text x="1.27" y="-3.7084" size="1.778" layer="95">&gt;NAME</text>
<text x="1.27" y="-5.715" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="VARISTOR">
<wire x1="2.54" y1="1.016" x2="2.54" y2="-1.016" width="0.254" layer="94"/>
<wire x1="2.54" y1="-1.016" x2="-2.54" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.016" x2="-2.54" y2="1.016" width="0.254" layer="94"/>
<wire x1="-2.54" y1="1.016" x2="2.54" y2="1.016" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.032" x2="2.032" y2="-2.032" width="0.254" layer="94"/>
<wire x1="-2.032" y1="2.032" x2="-2.54" y2="2.032" width="0.254" layer="94"/>
<wire x1="2.032" y1="-2.032" x2="-2.032" y2="2.032" width="0.254" layer="94"/>
<text x="-2.54" y="3.81" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-6.35" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="S10K250" prefix="R">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="VDR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="S10K250">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VARISTOR" prefix="R">
<description>&lt;b&gt;VARISTOR&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="VARISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="-2,5" package="R-5">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-7,5" package="R-7,5">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-5" package="R-5">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CN0402" package="CT/CN0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CN0603" package="CT/CN0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CN0805" package="CT/CN0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CN1206" package="CT/CN1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CN1210" package="CT/CN1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CN1812" package="CT/CN1812">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CN2220" package="CT/CN2220">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K11" package="S05K11">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K17" package="S05K17">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K175" package="S05K175">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K230" package="S05K230">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K250" package="S05K250">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K275" package="S05K275">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K300" package="S05K300">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K385" package="S05K385">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K40" package="S05K40">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K420" package="S05K420">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K440" package="S05K440">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S05K460" package="S05K460">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K11" package="S07K11">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K17" package="S07K17">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K175" package="S07K175">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K230" package="S07K230">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K250" package="S07K250">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K275" package="S07K275">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K285" package="S07K385">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K40" package="S07K40">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K420" package="S07K420">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K440" package="S07K440">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S07K460" package="S07K460">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CU3225K" package="CU3225K">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CU4032K" package="CU4032K">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="DGND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-2.667" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="DGND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DGND" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="DGND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="adafruit">
<packages>
<package name="DO41-10">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 2.54 mm, horizontal, grid 10.16 mm</description>
<wire x1="2.032" y1="-1.27" x2="-2.032" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.032" y1="-1.27" x2="2.032" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="1.27" x2="2.032" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="1.27" x2="-2.032" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="4.064" y2="0" width="0.762" layer="51"/>
<wire x1="-5.08" y1="0" x2="-4.064" y2="0" width="0.762" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<pad name="A" x="5.08" y="0" drill="1.1176" diameter="1.9304"/>
<pad name="C" x="-5.08" y="0" drill="1.1176" diameter="1.9304"/>
<text x="-2.032" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.032" y="-2.794" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-1.651" y1="-1.27" x2="-1.143" y2="1.27" layer="21"/>
<rectangle x1="2.032" y1="-0.381" x2="3.937" y2="0.381" layer="21"/>
<rectangle x1="-3.937" y1="-0.381" x2="-2.032" y2="0.381" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="D">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="1N4004" prefix="D">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
General purpose 1N400x type rectifier
&lt;p&gt;(With bigger pads)&lt;/p&gt;
&lt;p&gt;http://www.ladyada.net/library/pcb/eaglelibrary.html&lt;p&gt;</description>
<gates>
<gate name="1" symbol="D" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DO41-10">
<connects>
<connect gate="1" pin="A" pad="A"/>
<connect gate="1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diode">
<description>&lt;b&gt;Diodes&lt;/b&gt;&lt;p&gt;
Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Motorola : www.onsemi.com
&lt;li&gt;Fairchild : www.fairchildsemi.com
&lt;li&gt;Philips : www.semiconductors.com
&lt;li&gt;Vishay : www.vishay.de
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DO41-7.6">
<description>&lt;b&gt;DO41&lt;/b&gt; 7.6mm x 2mm&lt;p&gt;
Source: http://www.diodes.com/datasheets/ds23001.pdf</description>
<wire x1="2.082" y1="-0.92" x2="-2.082" y2="-0.92" width="0.1524" layer="21"/>
<wire x1="2.082" y1="-0.92" x2="2.082" y2="0.92" width="0.1524" layer="21"/>
<wire x1="-2.082" y1="0.92" x2="2.082" y2="0.92" width="0.1524" layer="21"/>
<wire x1="-2.082" y1="0.92" x2="-2.082" y2="-0.92" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0" x2="2.494" y2="0" width="0.85" layer="51"/>
<wire x1="-3.81" y1="0" x2="-2.519" y2="0" width="0.85" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<pad name="C" x="-3.81" y="0" drill="1.1" diameter="1.7"/>
<pad name="A" x="3.81" y="0" drill="1.1" diameter="1.7"/>
<text x="-2.032" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.032" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-1.651" y1="-0.95" x2="-1.143" y2="0.92" layer="21"/>
<rectangle x1="2.082" y1="-0.425" x2="2.717" y2="0.425" layer="21"/>
<rectangle x1="-2.717" y1="-0.425" x2="-2.082" y2="0.425" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="SCHOTTKY">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="1.016" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="-1.016" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<text x="-2.286" y="1.905" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.286" y="-3.429" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="1N581*" prefix="D">
<description>&lt;b&gt;1.0A SCHOTTKY BARRIER RECTIFIER&lt;/b&gt;&lt;p&gt;
Source: http://www.diodes.com/datasheets/ds23001.pdf</description>
<gates>
<gate name="G$1" symbol="SCHOTTKY" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DO41-7.6">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name="7-B"/>
<technology name="7-T"/>
<technology name="8-B"/>
<technology name="8-T"/>
<technology name="9-B"/>
<technology name="9-T"/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="resistor-power">
<description>&lt;b&gt;Vitrohm Power Resistors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="HS10">
<description>ARCOL Power Resistor 10W&lt;p&gt;
Distrib. RS Component</description>
<wire x1="8.15" y1="4.15" x2="8.15" y2="7.85" width="0.2032" layer="21"/>
<wire x1="8.15" y1="7.85" x2="3.35" y2="7.85" width="0.2032" layer="21"/>
<wire x1="-8.15" y1="-4.15" x2="8.15" y2="-4.15" width="0.2032" layer="21"/>
<wire x1="8.15" y1="-4.15" x2="8.15" y2="4.15" width="0.2032" layer="21"/>
<wire x1="8.15" y1="4.15" x2="3.35" y2="4.15" width="0.2032" layer="21"/>
<wire x1="3.35" y1="4.15" x2="-8.15" y2="4.15" width="0.2032" layer="21"/>
<wire x1="-8.15" y1="4.15" x2="-8.15" y2="-4.15" width="0.2032" layer="21"/>
<wire x1="3.35" y1="4.15" x2="3.35" y2="7.85" width="0.2032" layer="21"/>
<wire x1="-8.15" y1="-4.15" x2="-8.15" y2="-7.85" width="0.2032" layer="21"/>
<wire x1="-8.15" y1="-7.85" x2="-3.35" y2="-7.85" width="0.2032" layer="21"/>
<wire x1="-3.35" y1="-4.15" x2="-3.35" y2="-7.85" width="0.2032" layer="21"/>
<wire x1="-8.2" y1="0.5" x2="-15" y2="0.5" width="0.2032" layer="51"/>
<wire x1="-15" y1="0.5" x2="-15" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-15" y1="-0.5" x2="-8.2" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="8.2" y1="-0.5" x2="15" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="15" y1="-0.5" x2="15" y2="0.5" width="0.2032" layer="51"/>
<wire x1="15" y1="0.5" x2="8.2" y2="0.5" width="0.2032" layer="51"/>
<pad name="1" x="-12.7" y="0" drill="1.3" shape="octagon"/>
<pad name="2" x="12.7" y="0" drill="1.3" shape="octagon"/>
<text x="-6.35" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-6.35" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-8.5" y1="-4.5" x2="8.5" y2="4.5" layer="43"/>
<rectangle x1="3" y1="4.5" x2="8.5" y2="8.5" layer="43"/>
<rectangle x1="-8.5" y1="-8.5" x2="-3" y2="-4.5" layer="43"/>
<hole x="-5.65" y="-6.2" drill="2.4"/>
<hole x="5.65" y="6.2" drill="2.4"/>
</package>
<package name="HS15">
<description>ARCOL Power Resistor 15W&lt;p&gt;
Distrib. RS Component</description>
<wire x1="-9.85" y1="-10.4" x2="-4.25" y2="-10.4" width="0.2032" layer="21"/>
<wire x1="-9.85" y1="-5.5" x2="-9.85" y2="-10.4" width="0.2032" layer="21"/>
<wire x1="-9.85" y1="-5.5" x2="-4.25" y2="-5.5" width="0.2032" layer="21"/>
<wire x1="-4.25" y1="-5.5" x2="9.85" y2="-5.5" width="0.2032" layer="21"/>
<wire x1="9.85" y1="-5.5" x2="9.85" y2="5.5" width="0.2032" layer="21"/>
<wire x1="9.85" y1="5.5" x2="-9.85" y2="5.5" width="0.2032" layer="21"/>
<wire x1="-9.85" y1="5.5" x2="-9.85" y2="-5.5" width="0.2032" layer="21"/>
<wire x1="-4.25" y1="-5.5" x2="-4.25" y2="-10.4" width="0.2032" layer="21"/>
<wire x1="9.85" y1="10.4" x2="4.25" y2="10.4" width="0.2032" layer="21"/>
<wire x1="9.85" y1="5.5" x2="9.85" y2="10.4" width="0.2032" layer="21"/>
<wire x1="4.25" y1="5.5" x2="4.25" y2="10.4" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="-0.5" x2="-18.1" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-18.1" y1="-0.5" x2="-18.1" y2="0.5" width="0.2032" layer="51"/>
<wire x1="-18.1" y1="0.5" x2="-10" y2="0.5" width="0.2032" layer="51"/>
<wire x1="9.9" y1="0.5" x2="18.1" y2="0.5" width="0.2032" layer="51"/>
<wire x1="18.1" y1="0.5" x2="18.1" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="18.1" y1="-0.5" x2="10" y2="-0.5" width="0.2032" layer="51"/>
<pad name="1" x="-13.97" y="0" drill="1.3" shape="octagon"/>
<pad name="2" x="13.97" y="0" drill="1.3" shape="octagon"/>
<text x="-6.35" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-6.35" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-10.5" y1="-6" x2="10.5" y2="6" layer="43"/>
<rectangle x1="-10.5" y1="-11" x2="-4" y2="-6" layer="43"/>
<rectangle x1="3.5" y1="6" x2="10.5" y2="11" layer="43"/>
<hole x="-7.15" y="-7.95" drill="2.8"/>
<hole x="7.15" y="7.95" drill="2.8"/>
</package>
<package name="HS25">
<description>ARCOL Power Resistor 25W&lt;p&gt;
Distrib. RS Component</description>
<wire x1="13.55" y1="6.9" x2="13.55" y2="13.9" width="0.2032" layer="21"/>
<wire x1="13.55" y1="13.9" x2="4.15" y2="13.9" width="0.2032" layer="21"/>
<wire x1="-13.55" y1="-6.9" x2="13.55" y2="-6.9" width="0.2032" layer="21"/>
<wire x1="13.55" y1="-6.9" x2="13.55" y2="6.9" width="0.2032" layer="21"/>
<wire x1="13.55" y1="6.9" x2="4.15" y2="6.9" width="0.2032" layer="21"/>
<wire x1="4.15" y1="6.9" x2="-13.55" y2="6.9" width="0.2032" layer="21"/>
<wire x1="-13.55" y1="6.9" x2="-13.55" y2="-6.9" width="0.2032" layer="21"/>
<wire x1="4.15" y1="6.9" x2="4.15" y2="13.9" width="0.2032" layer="21"/>
<wire x1="-13.55" y1="-6.9" x2="-13.55" y2="-13.9" width="0.2032" layer="21"/>
<wire x1="-13.55" y1="-13.9" x2="-4.15" y2="-13.9" width="0.2032" layer="21"/>
<wire x1="-4.15" y1="-6.9" x2="-4.15" y2="-13.9" width="0.2032" layer="21"/>
<wire x1="-13.6" y1="-0.5" x2="-25.5" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-25.5" y1="-0.5" x2="-25.5" y2="0.5" width="0.2032" layer="51"/>
<wire x1="-25.5" y1="0.5" x2="-13.7" y2="0.5" width="0.2032" layer="51"/>
<wire x1="13.6" y1="0.5" x2="25.5" y2="0.5" width="0.2032" layer="51"/>
<wire x1="25.5" y1="0.5" x2="25.5" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="25.5" y1="-0.5" x2="13.7" y2="-0.5" width="0.2032" layer="51"/>
<pad name="1" x="-20.47" y="0" drill="1.3" shape="octagon"/>
<pad name="2" x="20.47" y="0" drill="1.3" shape="octagon"/>
<text x="-6.35" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-6.35" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-14" y1="-7.5" x2="14" y2="7.5" layer="43"/>
<rectangle x1="3.5" y1="7.5" x2="14" y2="14.5" layer="43"/>
<rectangle x1="-14" y1="-14.5" x2="-3.5" y2="-7.5" layer="43"/>
<hole x="9.15" y="9.9" drill="3.2"/>
<hole x="-9.15" y="-9.9" drill="3.2"/>
</package>
<package name="HS50">
<description>ARCOL Power Resistor 50W&lt;p&gt;
Distrib. RS Component</description>
<wire x1="24.95" y1="7" x2="24.95" y2="14.55" width="0.2032" layer="21"/>
<wire x1="24.95" y1="14.55" x2="14.55" y2="14.55" width="0.2032" layer="21"/>
<wire x1="-24.95" y1="-7" x2="24.95" y2="-7" width="0.2032" layer="21"/>
<wire x1="24.95" y1="-7" x2="24.95" y2="7" width="0.2032" layer="21"/>
<wire x1="24.95" y1="7" x2="14.55" y2="7" width="0.2032" layer="21"/>
<wire x1="14.55" y1="7" x2="-24.95" y2="7" width="0.2032" layer="21"/>
<wire x1="-24.95" y1="7" x2="-24.95" y2="-7" width="0.2032" layer="21"/>
<wire x1="14.55" y1="7" x2="14.55" y2="14.55" width="0.2032" layer="21"/>
<wire x1="-24.95" y1="-7" x2="-24.95" y2="-14.55" width="0.2032" layer="21"/>
<wire x1="-24.95" y1="-14.55" x2="-14.55" y2="-14.55" width="0.2032" layer="21"/>
<wire x1="-14.55" y1="-7" x2="-14.55" y2="-14.55" width="0.2032" layer="21"/>
<wire x1="-25" y1="0.5" x2="-36" y2="0.5" width="0.2032" layer="51"/>
<wire x1="-36" y1="0.5" x2="-36" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-36" y1="-0.5" x2="-25.1" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="25" y1="-0.5" x2="36" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="36" y1="-0.5" x2="36" y2="0.5" width="0.2032" layer="51"/>
<wire x1="36" y1="0.5" x2="25.1" y2="0.5" width="0.2032" layer="51"/>
<pad name="1" x="-31.47" y="0" drill="1.3" shape="octagon"/>
<pad name="2" x="31.47" y="0" drill="1.3" shape="octagon"/>
<text x="-6.35" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-6.35" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-25.5" y1="-7.5" x2="25.5" y2="7.5" layer="43"/>
<rectangle x1="14" y1="7.5" x2="25.5" y2="15" layer="43"/>
<rectangle x1="-25.5" y1="-15" x2="-14" y2="-7.5" layer="43"/>
<hole x="19.85" y="10.7" drill="3.2"/>
<hole x="-19.85" y="-10.7" drill="3.2"/>
</package>
<package name="KH206-8">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
4W, grid 26,67 mm</description>
<wire x1="-10.16" y1="-3.175" x2="10.16" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="10.16" y1="3.175" x2="-10.16" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="3.175" x2="-10.16" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-3.175" x2="10.16" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="0" x2="-11.43" y2="0" width="0.8128" layer="51"/>
<wire x1="11.43" y1="0" x2="13.335" y2="0" width="0.8128" layer="51"/>
<pad name="1" x="-13.335" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="13.335" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-9.144" y="0.508" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-9.144" y="-2.286" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="4.572" y="-2.286" size="1.778" layer="21" ratio="10">4W</text>
<text x="4.572" y="0.508" size="1.778" layer="21" ratio="10">206</text>
<rectangle x1="-11.3284" y1="-0.4064" x2="-10.16" y2="0.4064" layer="21"/>
<rectangle x1="10.16" y1="-0.4064" x2="11.3284" y2="0.4064" layer="21"/>
</package>
<package name="KH206-8R">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
4W, grid 5,08 mm</description>
<wire x1="-5.08" y1="-3.175" x2="0" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="0" y1="3.175" x2="-5.08" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="0.889" y2="0" width="0.8128" layer="51"/>
<wire x1="0.635" y1="0" x2="-0.635" y2="0" width="0.8128" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="0" x2="-2.54" y2="0" width="0.8128" layer="51"/>
<wire x1="0" y1="3.175" x2="0.635" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="0" y1="-3.175" x2="0.635" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.715" y1="-2.54" x2="-5.08" y2="-3.175" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="3.175" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-2.54" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-5.08" y="3.556" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="1.524" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.08" y="-2.921" size="1.27" layer="21" ratio="10">4W</text>
</package>
<package name="KH208-8">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
5W, grid 31,75 mm</description>
<wire x1="-12.573" y1="-3.175" x2="12.573" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="12.573" y1="3.175" x2="-12.573" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-12.573" y1="3.175" x2="-12.573" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="12.573" y1="-3.175" x2="12.573" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="0" x2="-13.97" y2="0" width="0.8128" layer="51"/>
<wire x1="13.97" y1="0" x2="15.875" y2="0" width="0.8128" layer="51"/>
<pad name="1" x="-15.875" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="15.875" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-11.43" y="0.381" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-11.43" y="-2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="6.35" y="-2.159" size="1.778" layer="21" ratio="10">5W</text>
<text x="6.35" y="0.381" size="1.778" layer="21" ratio="10">208</text>
<rectangle x1="-13.8938" y1="-0.4064" x2="-12.573" y2="0.4064" layer="21"/>
<rectangle x1="12.573" y1="-0.4064" x2="13.8938" y2="0.4064" layer="21"/>
</package>
<package name="KH208R-8">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
5W, grid 5,08 mm</description>
<wire x1="-5.08" y1="-3.175" x2="0" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="0" y1="3.175" x2="-5.08" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="0.889" y2="0" width="0.8128" layer="51"/>
<wire x1="0.635" y1="0" x2="-0.635" y2="0" width="0.8128" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="0" x2="-2.54" y2="0" width="0.8128" layer="51"/>
<wire x1="-5.715" y1="-2.54" x2="-5.08" y2="-3.175" width="0.1524" layer="21" curve="90"/>
<wire x1="0" y1="-3.175" x2="0.635" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="0" y1="3.175" x2="0.635" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="3.175" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-2.54" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-5.08" y="3.429" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="1.524" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.08" y="-2.921" size="1.27" layer="21" ratio="10">5W</text>
</package>
<package name="KH214-8">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
9W, grid 43,18 mm</description>
<wire x1="-19.05" y1="-4.572" x2="19.05" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="19.05" y1="4.572" x2="-19.05" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="4.572" x2="-19.05" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="19.05" y1="-4.572" x2="19.05" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="0" x2="-20.32" y2="0" width="0.8128" layer="51"/>
<wire x1="20.32" y1="0" x2="21.59" y2="0" width="0.8128" layer="51"/>
<pad name="1" x="-21.59" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="21.59" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-17.145" y="0.635" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-17.145" y="-2.54" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="12.7" y="-2.54" size="1.778" layer="21" ratio="10">9W</text>
<text x="12.7" y="0.762" size="1.778" layer="21" ratio="10">214</text>
<rectangle x1="19.05" y1="-0.4064" x2="20.193" y2="0.4064" layer="21"/>
<rectangle x1="-20.193" y1="-0.4064" x2="-19.05" y2="0.4064" layer="21"/>
</package>
<package name="KH214R-8">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
9W, grid 5,08 mm</description>
<wire x1="-6.35" y1="-4.445" x2="1.27" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="1.27" y1="4.445" x2="-6.35" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="3.81" x2="-6.985" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-3.81" x2="1.905" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="3.175" y1="0" x2="1.524" y2="0" width="0.8128" layer="51"/>
<wire x1="1.27" y1="0" x2="-0.635" y2="0" width="0.8128" layer="21"/>
<wire x1="1.905" y1="0.889" x2="1.905" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="0" x2="-2.54" y2="0" width="0.8128" layer="51"/>
<wire x1="1.905" y1="-0.889" x2="1.905" y2="0.889" width="0.1524" layer="51"/>
<wire x1="1.27" y1="-4.445" x2="1.905" y2="-3.81" width="0.1524" layer="21" curve="90"/>
<wire x1="1.27" y1="4.445" x2="1.905" y2="3.81" width="0.1524" layer="21" curve="-90"/>
<wire x1="-6.985" y1="3.81" x2="-6.35" y2="4.445" width="0.1524" layer="21" curve="-90"/>
<wire x1="-6.985" y1="-3.81" x2="-6.35" y2="-4.445" width="0.1524" layer="21" curve="90"/>
<pad name="1" x="-2.54" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="3.175" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-6.985" y="4.826" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.35" y="2.032" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="-6.477" y="-3.937" size="1.778" layer="21" ratio="10">9W</text>
</package>
<package name="KH216-8">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
11W, grid 55,88 mm</description>
<wire x1="-25.4" y1="-4.572" x2="25.4" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="25.4" y1="4.572" x2="-25.4" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="4.572" x2="-25.4" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="25.4" y1="-4.572" x2="25.4" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-27.94" y1="0" x2="-26.67" y2="0" width="0.8128" layer="51"/>
<wire x1="26.67" y1="0" x2="27.94" y2="0" width="0.8128" layer="51"/>
<pad name="1" x="-27.94" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="27.94" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-22.86" y="0.635" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-22.86" y="-2.54" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="19.05" y="0.762" size="1.778" layer="21" ratio="10">216</text>
<text x="19.05" y="-2.54" size="1.778" layer="21" ratio="10">11W</text>
<rectangle x1="25.4" y1="-0.4064" x2="26.543" y2="0.4064" layer="21"/>
<rectangle x1="-26.543" y1="-0.4064" x2="-25.4" y2="0.4064" layer="21"/>
</package>
<package name="KH218-8">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
17W, grid 80,01 mm</description>
<wire x1="-37.465" y1="-4.572" x2="37.465" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="37.465" y1="4.572" x2="-37.465" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-37.465" y1="4.572" x2="-37.465" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="37.465" y1="-4.572" x2="37.465" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-40.005" y1="0" x2="-38.735" y2="0" width="0.8128" layer="51"/>
<wire x1="38.735" y1="0" x2="40.005" y2="0" width="0.8128" layer="51"/>
<pad name="1" x="-40.005" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<pad name="2" x="40.005" y="0" drill="1.016" diameter="2.54" shape="octagon"/>
<text x="-34.925" y="0.635" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-34.925" y="-2.54" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="31.115" y="0.762" size="1.778" layer="21" ratio="10">218</text>
<text x="31.115" y="-2.54" size="1.778" layer="21" ratio="10">17W</text>
<rectangle x1="37.465" y1="-0.4064" x2="38.608" y2="0.4064" layer="21"/>
<rectangle x1="-38.608" y1="-0.4064" x2="-37.465" y2="0.4064" layer="21"/>
</package>
<package name="KP290">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
0518, 2W, grid 10,16 mm</description>
<wire x1="-3.1968" y1="2.032" x2="3.1968" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-3.1968" y1="-2.032" x2="3.1968" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-9.144" y1="1.524" x2="-9.144" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-3.937" y1="-1.524" x2="-3.937" y2="1.524" width="0.1524" layer="51"/>
<wire x1="-3.302" y1="-0.6839" x2="-3.302" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="-8.128" y1="-2.54" x2="-3.9152" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.144" y1="-1.524" x2="-8.128" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="-3.3764" y1="-2.1064" x2="-3.1968" y2="-2.0319" width="0.1524" layer="21" curve="-44.989981"/>
<wire x1="-3.7356" y1="-2.4656" x2="-3.3764" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="-3.9152" y1="-2.54" x2="-3.7356" y2="-2.4656" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="-3.937" y1="-2.286" x2="-3.937" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="-1.778" x2="-3.302" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="-8.128" y1="2.54" x2="-3.9152" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.144" y1="1.524" x2="-8.128" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.3764" y1="2.1064" x2="-3.1968" y2="2.0319" width="0.1524" layer="21" curve="44.989981"/>
<wire x1="-3.7356" y1="2.4656" x2="-3.3764" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="-3.9152" y1="2.54" x2="-3.7356" y2="2.4656" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="-3.937" y1="1.524" x2="-3.937" y2="2.159" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="0.6839" x2="-3.302" y2="1.778" width="0.1524" layer="21"/>
<wire x1="9.144" y1="1.524" x2="9.144" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="3.937" y1="-1.524" x2="3.937" y2="1.524" width="0.1524" layer="51"/>
<wire x1="3.302" y1="-0.6839" x2="3.302" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="3.9152" y1="-2.54" x2="8.128" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.1968" y1="-2.032" x2="3.3764" y2="-2.1064" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="3.7356" y1="-2.4656" x2="3.3764" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="3.7356" y1="-2.4656" x2="3.9152" y2="-2.54" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="3.302" y1="-1.778" x2="3.302" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="3.937" y1="-2.286" x2="3.937" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="8.128" y1="-2.54" x2="9.144" y2="-1.524" width="0.1524" layer="21" curve="90"/>
<wire x1="3.9152" y1="2.54" x2="8.128" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.7356" y1="2.4656" x2="3.9152" y2="2.54" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="3.7356" y1="2.4656" x2="3.3764" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="3.1968" y1="2.032" x2="3.3764" y2="2.1064" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="3.302" y1="0.6839" x2="3.302" y2="1.778" width="0.1524" layer="21"/>
<wire x1="3.937" y1="1.524" x2="3.937" y2="2.159" width="0.1524" layer="21"/>
<wire x1="8.128" y1="2.54" x2="9.144" y2="1.524" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-5.08" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="5.08" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-2.54" y="2.54" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="8.636" y="-1.143" size="1.27" layer="21" ratio="10" rot="R90">2W</text>
<text x="-6.985" y="-2.159" size="1.27" layer="21" ratio="10" rot="R90">0518</text>
</package>
<package name="KP292">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
0523, 4W, grid 15,24 mm</description>
<wire x1="-5.7368" y1="2.032" x2="5.7368" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-5.7368" y1="-2.032" x2="5.7368" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-11.684" y1="1.524" x2="-11.684" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-6.477" y1="-1.524" x2="-6.477" y2="1.524" width="0.1524" layer="51"/>
<wire x1="-5.842" y1="-0.6839" x2="-5.842" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="-10.668" y1="-2.54" x2="-6.4552" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-11.684" y1="-1.524" x2="-10.668" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.9164" y1="-2.1064" x2="-5.7368" y2="-2.0319" width="0.1524" layer="21" curve="-44.989981"/>
<wire x1="-6.2756" y1="-2.4656" x2="-5.9164" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="-6.4552" y1="-2.54" x2="-6.2756" y2="-2.4656" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="-6.477" y1="-2.286" x2="-6.477" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-5.842" y1="-1.778" x2="-5.842" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="-10.668" y1="2.54" x2="-6.4552" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-11.684" y1="1.524" x2="-10.668" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.9164" y1="2.1064" x2="-5.7368" y2="2.0319" width="0.1524" layer="21" curve="44.989981"/>
<wire x1="-6.2756" y1="2.4656" x2="-5.9164" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="-6.4552" y1="2.54" x2="-6.2756" y2="2.4656" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="-6.477" y1="1.524" x2="-6.477" y2="2.159" width="0.1524" layer="21"/>
<wire x1="-5.842" y1="0.6839" x2="-5.842" y2="1.778" width="0.1524" layer="21"/>
<wire x1="11.684" y1="1.524" x2="11.684" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="6.477" y1="-1.524" x2="6.477" y2="1.524" width="0.1524" layer="51"/>
<wire x1="5.842" y1="-0.6839" x2="5.842" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="6.4552" y1="-2.54" x2="10.668" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.7368" y1="-2.032" x2="5.9164" y2="-2.1064" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="6.2756" y1="-2.4656" x2="5.9164" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="6.2756" y1="-2.4656" x2="6.4552" y2="-2.54" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="5.842" y1="-1.778" x2="5.842" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="6.477" y1="-2.286" x2="6.477" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="10.668" y1="-2.54" x2="11.684" y2="-1.524" width="0.1524" layer="21" curve="90"/>
<wire x1="6.4552" y1="2.54" x2="10.668" y2="2.54" width="0.1524" layer="21"/>
<wire x1="6.2756" y1="2.4656" x2="6.4552" y2="2.54" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="6.2756" y1="2.4656" x2="5.9164" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="5.7368" y1="2.032" x2="5.9164" y2="2.1064" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="5.842" y1="0.6839" x2="5.842" y2="1.778" width="0.1524" layer="21"/>
<wire x1="6.477" y1="1.524" x2="6.477" y2="2.159" width="0.1524" layer="21"/>
<wire x1="10.668" y1="2.54" x2="11.684" y2="1.524" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-7.62" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="7.62" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-5.08" y="2.54" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="11.049" y="-1.143" size="1.27" layer="21" ratio="10" rot="R90">4W</text>
<text x="-9.525" y="-2.286" size="1.27" layer="21" ratio="10" rot="R90">0523</text>
</package>
<package name="KP294">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
0533, 5W, grid 25,4 mm</description>
<wire x1="-10.8168" y1="2.032" x2="10.8168" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-10.8168" y1="-2.032" x2="10.8168" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="1.524" x2="-16.764" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-11.557" y1="-1.524" x2="-11.557" y2="1.524" width="0.1524" layer="51"/>
<wire x1="-10.922" y1="-0.6839" x2="-10.922" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="-15.748" y1="-2.54" x2="-11.5352" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="-1.524" x2="-15.748" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="-10.9964" y1="-2.1064" x2="-10.8168" y2="-2.0319" width="0.1524" layer="21" curve="-44.989981"/>
<wire x1="-11.3556" y1="-2.4656" x2="-10.9964" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="-11.5352" y1="-2.54" x2="-11.3556" y2="-2.4656" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="-11.557" y1="-2.286" x2="-11.557" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-10.922" y1="-1.778" x2="-10.922" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="-15.748" y1="2.54" x2="-11.5352" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-16.764" y1="1.524" x2="-15.748" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="-10.9964" y1="2.1064" x2="-10.8168" y2="2.0319" width="0.1524" layer="21" curve="44.989981"/>
<wire x1="-11.3556" y1="2.4656" x2="-10.9964" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="-11.5352" y1="2.54" x2="-11.3556" y2="2.4656" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="-11.557" y1="1.524" x2="-11.557" y2="2.159" width="0.1524" layer="21"/>
<wire x1="-10.922" y1="0.6839" x2="-10.922" y2="1.778" width="0.1524" layer="21"/>
<wire x1="16.764" y1="1.524" x2="16.764" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="11.557" y1="-1.524" x2="11.557" y2="1.524" width="0.1524" layer="51"/>
<wire x1="10.922" y1="-0.6839" x2="10.922" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="11.5352" y1="-2.54" x2="15.748" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.8168" y1="-2.032" x2="10.9964" y2="-2.1064" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="11.3556" y1="-2.4656" x2="10.9964" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="11.3556" y1="-2.4656" x2="11.5352" y2="-2.54" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="10.922" y1="-1.778" x2="10.922" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="11.557" y1="-2.286" x2="11.557" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="15.748" y1="-2.54" x2="16.764" y2="-1.524" width="0.1524" layer="21" curve="90"/>
<wire x1="11.5352" y1="2.54" x2="15.748" y2="2.54" width="0.1524" layer="21"/>
<wire x1="11.3556" y1="2.4656" x2="11.5352" y2="2.54" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="11.3556" y1="2.4656" x2="10.9964" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="10.8168" y1="2.032" x2="10.9964" y2="2.1064" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="10.922" y1="0.6839" x2="10.922" y2="1.778" width="0.1524" layer="21"/>
<wire x1="11.557" y1="1.524" x2="11.557" y2="2.159" width="0.1524" layer="21"/>
<wire x1="15.748" y1="2.54" x2="16.764" y2="1.524" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-12.7" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="12.7" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-7.62" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-7.62" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="5.08" y="-1.524" size="1.27" layer="21" ratio="10">5W</text>
<text x="5.08" y="0.254" size="1.27" layer="21" ratio="10">0533</text>
</package>
<package name="KP296">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
0543, 6,5W, grid 35,4 mm</description>
<wire x1="-15.8968" y1="2.032" x2="15.8968" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-15.8968" y1="-2.032" x2="15.8968" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-21.844" y1="1.524" x2="-21.844" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-16.637" y1="-1.524" x2="-16.637" y2="1.524" width="0.1524" layer="51"/>
<wire x1="-16.002" y1="-0.6839" x2="-16.002" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="-20.828" y1="-2.54" x2="-16.6152" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-21.844" y1="-1.524" x2="-20.828" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="-16.0764" y1="-2.1064" x2="-15.8968" y2="-2.0319" width="0.1524" layer="21" curve="-44.989981"/>
<wire x1="-16.4356" y1="-2.4656" x2="-16.0764" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="-16.6152" y1="-2.54" x2="-16.4356" y2="-2.4656" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="-16.637" y1="-2.286" x2="-16.637" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-16.002" y1="-1.778" x2="-16.002" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="-20.828" y1="2.54" x2="-16.6152" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-21.844" y1="1.524" x2="-20.828" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="-16.0764" y1="2.1064" x2="-15.8968" y2="2.0319" width="0.1524" layer="21" curve="44.989981"/>
<wire x1="-16.4356" y1="2.4656" x2="-16.0764" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="-16.6152" y1="2.54" x2="-16.4356" y2="2.4656" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="-16.637" y1="1.524" x2="-16.637" y2="2.159" width="0.1524" layer="21"/>
<wire x1="-16.002" y1="0.6839" x2="-16.002" y2="1.778" width="0.1524" layer="21"/>
<wire x1="21.844" y1="1.524" x2="21.844" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="16.637" y1="-1.524" x2="16.637" y2="1.524" width="0.1524" layer="51"/>
<wire x1="16.002" y1="-0.6839" x2="16.002" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="16.6152" y1="-2.54" x2="20.828" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="15.8968" y1="-2.032" x2="16.0764" y2="-2.1064" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="16.4356" y1="-2.4656" x2="16.0764" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="16.4356" y1="-2.4656" x2="16.6152" y2="-2.54" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="16.002" y1="-1.778" x2="16.002" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="16.637" y1="-2.286" x2="16.637" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="20.828" y1="-2.54" x2="21.844" y2="-1.524" width="0.1524" layer="21" curve="90"/>
<wire x1="16.6152" y1="2.54" x2="20.828" y2="2.54" width="0.1524" layer="21"/>
<wire x1="16.4356" y1="2.4656" x2="16.6152" y2="2.54" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="16.4356" y1="2.4656" x2="16.0764" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="15.8968" y1="2.032" x2="16.0764" y2="2.1064" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="16.002" y1="0.6839" x2="16.002" y2="1.778" width="0.1524" layer="21"/>
<wire x1="16.637" y1="1.524" x2="16.637" y2="2.159" width="0.1524" layer="21"/>
<wire x1="20.828" y1="2.54" x2="21.844" y2="1.524" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-17.78" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="17.78" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-12.7" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-12.7" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="10.16" y="-1.524" size="1.27" layer="21" ratio="10">6,5W</text>
<text x="10.16" y="0.254" size="1.27" layer="21" ratio="10">0543</text>
</package>
<package name="KP298">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
0553, 8W, grid 45,7 mm</description>
<wire x1="-20.9768" y1="2.032" x2="20.9768" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-20.9768" y1="-2.032" x2="20.9768" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-26.924" y1="1.524" x2="-26.924" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-21.717" y1="-1.524" x2="-21.717" y2="1.524" width="0.1524" layer="51"/>
<wire x1="-21.082" y1="-0.6839" x2="-21.082" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="-25.908" y1="-2.54" x2="-21.6952" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-26.924" y1="-1.524" x2="-25.908" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="-21.1564" y1="-2.1064" x2="-20.9768" y2="-2.0319" width="0.1524" layer="21" curve="-44.989981"/>
<wire x1="-21.5156" y1="-2.4656" x2="-21.1564" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="-21.6952" y1="-2.54" x2="-21.5156" y2="-2.4656" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="-21.717" y1="-2.286" x2="-21.717" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-21.082" y1="-1.778" x2="-21.082" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="-25.908" y1="2.54" x2="-21.6952" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-26.924" y1="1.524" x2="-25.908" y2="2.54" width="0.1524" layer="21" curve="-90"/>
<wire x1="-21.1564" y1="2.1064" x2="-20.9768" y2="2.0319" width="0.1524" layer="21" curve="44.989981"/>
<wire x1="-21.5156" y1="2.4656" x2="-21.1564" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="-21.6952" y1="2.54" x2="-21.5156" y2="2.4656" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="-21.717" y1="1.524" x2="-21.717" y2="2.159" width="0.1524" layer="21"/>
<wire x1="-21.082" y1="0.6839" x2="-21.082" y2="1.778" width="0.1524" layer="21"/>
<wire x1="26.924" y1="1.524" x2="26.924" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="21.717" y1="-1.524" x2="21.717" y2="1.524" width="0.1524" layer="51"/>
<wire x1="21.082" y1="-0.6839" x2="21.082" y2="0.6839" width="0.1524" layer="51"/>
<wire x1="21.6952" y1="-2.54" x2="25.908" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="20.9768" y1="-2.032" x2="21.1564" y2="-2.1064" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="21.5156" y1="-2.4656" x2="21.1564" y2="-2.1064" width="0.1524" layer="21"/>
<wire x1="21.5156" y1="-2.4656" x2="21.6952" y2="-2.54" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="21.082" y1="-1.778" x2="21.082" y2="-0.6839" width="0.1524" layer="21"/>
<wire x1="21.717" y1="-2.286" x2="21.717" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="25.908" y1="-2.54" x2="26.924" y2="-1.524" width="0.1524" layer="21" curve="90"/>
<wire x1="21.6952" y1="2.54" x2="25.908" y2="2.54" width="0.1524" layer="21"/>
<wire x1="21.5156" y1="2.4656" x2="21.6952" y2="2.54" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="21.5156" y1="2.4656" x2="21.1564" y2="2.1064" width="0.1524" layer="21"/>
<wire x1="20.9768" y1="2.032" x2="21.1564" y2="2.1064" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="21.082" y1="0.6839" x2="21.082" y2="1.778" width="0.1524" layer="21"/>
<wire x1="21.717" y1="1.524" x2="21.717" y2="2.159" width="0.1524" layer="21"/>
<wire x1="25.908" y1="2.54" x2="26.924" y2="1.524" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-22.86" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="22.86" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-7.62" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-7.62" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="15.24" y="-1.651" size="1.27" layer="21" ratio="10">8W</text>
<text x="15.24" y="0.254" size="1.27" layer="21" ratio="10">0553</text>
</package>
<package name="KWP330">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
3W, grid 10 mm</description>
<wire x1="-11.557" y1="5.08" x2="-11.557" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-11.557" y1="-5.08" x2="11.557" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="11.557" y1="-5.08" x2="11.557" y2="5.08" width="0.1524" layer="21"/>
<wire x1="11.557" y1="5.08" x2="-11.557" y2="5.08" width="0.1524" layer="21"/>
<wire x1="11.176" y1="-4.699" x2="11.176" y2="4.699" width="0.1524" layer="21"/>
<wire x1="11.176" y1="4.699" x2="-11.176" y2="4.699" width="0.1524" layer="21"/>
<wire x1="-11.176" y1="4.699" x2="-11.176" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="-11.176" y1="-4.699" x2="11.176" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="11.176" y1="-4.699" x2="11.557" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="11.176" y1="4.699" x2="11.557" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-11.176" y1="4.699" x2="-11.557" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-11.176" y1="-4.699" x2="-11.557" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-3.175" x2="2.54" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-3.175" x2="2.54" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-2.54" x2="-5.08" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="2.54" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-5.08" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="5.08" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-11.557" y="5.461" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-10.16" y="2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="7.493" y="0" size="1.778" layer="21" ratio="10">3W</text>
<text x="5.842" y="2.54" size="1.778" layer="21" ratio="10">330</text>
</package>
<package name="KWP332">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
5W, grid 15 mm</description>
<wire x1="-14.097" y1="5.08" x2="-14.097" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-14.097" y1="-5.08" x2="14.097" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="14.097" y1="-5.08" x2="14.097" y2="5.08" width="0.1524" layer="21"/>
<wire x1="14.097" y1="5.08" x2="-14.097" y2="5.08" width="0.1524" layer="21"/>
<wire x1="13.716" y1="-4.699" x2="13.716" y2="4.699" width="0.1524" layer="21"/>
<wire x1="13.716" y1="4.699" x2="-13.716" y2="4.699" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="4.699" x2="-13.716" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="-4.699" x2="13.716" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="13.716" y1="-4.699" x2="14.097" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="13.716" y1="4.699" x2="14.097" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="4.699" x2="-14.097" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="-4.699" x2="-14.097" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-5.08" y2="0" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-7.493" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="7.493" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-14.097" y="5.461" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-7.62" y="2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="10.033" y="0" size="1.778" layer="21" ratio="10">5W</text>
<text x="8.382" y="2.54" size="1.778" layer="21" ratio="10">332</text>
</package>
<package name="KWP333">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
7W, grid 22,5 mm</description>
<wire x1="-17.526" y1="5.08" x2="-17.526" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-17.526" y1="-5.08" x2="17.526" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="17.526" y1="-5.08" x2="17.526" y2="5.08" width="0.1524" layer="21"/>
<wire x1="17.526" y1="5.08" x2="-17.526" y2="5.08" width="0.1524" layer="21"/>
<wire x1="17.145" y1="-4.699" x2="17.145" y2="4.699" width="0.1524" layer="21"/>
<wire x1="17.145" y1="4.699" x2="-17.145" y2="4.699" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="4.699" x2="-17.145" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="-4.699" x2="17.145" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="17.145" y1="-4.699" x2="17.526" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="17.145" y1="4.699" x2="17.526" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="4.699" x2="-17.526" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="-4.699" x2="-17.526" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-5.08" y2="0" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-11.303" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="11.303" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-17.526" y="5.461" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-11.049" y="2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="13.335" y="0" size="1.778" layer="21" ratio="10">7W</text>
<text x="11.811" y="2.54" size="1.778" layer="21" ratio="10">333</text>
</package>
<package name="KWP335">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
9W, grid 30 mm</description>
<wire x1="-21.59" y1="5.08" x2="-21.59" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="-5.08" x2="21.59" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="21.59" y1="-5.08" x2="21.59" y2="5.08" width="0.1524" layer="21"/>
<wire x1="21.59" y1="5.08" x2="-21.59" y2="5.08" width="0.1524" layer="21"/>
<wire x1="21.209" y1="-4.699" x2="21.209" y2="4.699" width="0.1524" layer="21"/>
<wire x1="21.209" y1="4.699" x2="-21.209" y2="4.699" width="0.1524" layer="21"/>
<wire x1="-21.209" y1="4.699" x2="-21.209" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="-21.209" y1="-4.699" x2="21.209" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="21.209" y1="-4.699" x2="21.59" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="21.209" y1="4.699" x2="21.59" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-21.209" y1="4.699" x2="-21.59" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-21.209" y1="-4.699" x2="-21.59" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-5.08" y2="0" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-14.986" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="14.986" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-21.59" y="5.461" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-15.113" y="2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="17.526" y="0" size="1.778" layer="21" ratio="10">9W</text>
<text x="15.875" y="2.54" size="1.778" layer="21" ratio="10">335</text>
</package>
<package name="KWP336">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
10W, grid 35 mm</description>
<wire x1="-24.003" y1="5.08" x2="-24.003" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-24.003" y1="-5.08" x2="24.003" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="24.003" y1="-5.08" x2="24.003" y2="5.08" width="0.1524" layer="21"/>
<wire x1="24.003" y1="5.08" x2="-24.003" y2="5.08" width="0.1524" layer="21"/>
<wire x1="23.622" y1="-4.699" x2="23.622" y2="4.699" width="0.1524" layer="21"/>
<wire x1="23.622" y1="4.699" x2="-23.622" y2="4.699" width="0.1524" layer="21"/>
<wire x1="-23.622" y1="4.699" x2="-23.622" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="-23.622" y1="-4.699" x2="23.622" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="23.622" y1="-4.699" x2="24.003" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="23.622" y1="4.699" x2="24.003" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-23.622" y1="4.699" x2="-24.003" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-23.622" y1="-4.699" x2="-24.003" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-5.08" y2="0" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-17.526" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="17.526" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-24.003" y="5.461" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-17.526" y="2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="17.78" y="-3.937" size="1.778" layer="21" ratio="10">10W</text>
<text x="17.78" y="2.159" size="1.778" layer="21" ratio="10">336</text>
</package>
<package name="KWP337">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
15W, grid 32,5 mm</description>
<wire x1="-25.019" y1="5.08" x2="-25.019" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-25.019" y1="-5.08" x2="25.019" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="25.019" y1="-5.08" x2="25.019" y2="5.08" width="0.1524" layer="21"/>
<wire x1="25.019" y1="5.08" x2="-25.019" y2="5.08" width="0.1524" layer="21"/>
<wire x1="24.638" y1="-4.699" x2="24.638" y2="4.699" width="0.1524" layer="21"/>
<wire x1="24.638" y1="4.699" x2="-24.638" y2="4.699" width="0.1524" layer="21"/>
<wire x1="-24.638" y1="4.699" x2="-24.638" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="-24.638" y1="-4.699" x2="24.638" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="24.638" y1="-4.699" x2="25.019" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="24.638" y1="4.699" x2="25.019" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-24.638" y1="4.699" x2="-25.019" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-24.638" y1="-4.699" x2="-25.019" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-5.08" y2="0" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-16.256" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="16.256" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-25.019" y="5.461" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-18.542" y="2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="17.78" y="-3.937" size="1.778" layer="21" ratio="10">15W</text>
<text x="17.78" y="2.159" size="1.778" layer="21" ratio="10">337</text>
</package>
<package name="KWP338">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
20W, grid 47,5 mm</description>
<wire x1="-32.512" y1="5.08" x2="-32.512" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-32.512" y1="-5.08" x2="32.512" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="32.512" y1="-5.08" x2="32.512" y2="5.08" width="0.1524" layer="21"/>
<wire x1="32.512" y1="5.08" x2="-32.512" y2="5.08" width="0.1524" layer="21"/>
<wire x1="32.131" y1="-4.699" x2="32.131" y2="4.699" width="0.1524" layer="21"/>
<wire x1="32.131" y1="4.699" x2="-32.131" y2="4.699" width="0.1524" layer="21"/>
<wire x1="-32.131" y1="4.699" x2="-32.131" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="-32.131" y1="-4.699" x2="32.131" y2="-4.699" width="0.1524" layer="21"/>
<wire x1="32.131" y1="-4.699" x2="32.512" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="32.131" y1="4.699" x2="32.512" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-32.131" y1="4.699" x2="-32.512" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-32.131" y1="-4.699" x2="-32.512" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-5.08" y2="0" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-23.749" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<pad name="2" x="23.749" y="0" drill="1.3208" diameter="3.1496" shape="octagon"/>
<text x="-32.512" y="5.461" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-26.035" y="2.159" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="25.4" y="2.159" size="1.778" layer="21" ratio="10">338</text>
<text x="25.4" y="-4.064" size="1.778" layer="21" ratio="10">20W</text>
</package>
<package name="MNS-2">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
CWR-2/COR-2, 2W, grid 5 mm&lt;p&gt;
Buerklin</description>
<wire x1="-5.588" y1="-3.556" x2="5.588" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="5.588" y1="-3.556" x2="5.588" y2="3.556" width="0.1524" layer="21"/>
<wire x1="5.588" y1="3.556" x2="-5.588" y2="3.556" width="0.1524" layer="21"/>
<wire x1="-5.588" y1="3.556" x2="-5.588" y2="-3.556" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-2.159" x2="-3.81" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-2.921" x2="0" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="0" y1="-2.921" x2="0" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-2.159" x2="-3.81" y2="-2.159" width="0.1524" layer="21"/>
<wire x1="0" y1="-2.54" x2="0.889" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-2.159" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-2.54" x2="-4.699" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-2.54" x2="-3.81" y2="-2.921" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="1.1938" diameter="2.54" shape="octagon"/>
<pad name="2" x="2.54" y="0" drill="1.1938" diameter="2.54" shape="octagon"/>
<text x="-5.08" y="4.064" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="1.778" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="2.794" y="-3.048" size="1.27" layer="21" ratio="10">2W</text>
</package>
<package name="MNS-5">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
CWR-5/COR-5, 5W, grid 5 mm&lt;p&gt;
Buerklin</description>
<wire x1="-6.604" y1="-4.572" x2="6.604" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="6.604" y1="-4.572" x2="6.604" y2="4.572" width="0.1524" layer="21"/>
<wire x1="6.604" y1="4.572" x2="-6.604" y2="4.572" width="0.1524" layer="21"/>
<wire x1="-6.604" y1="4.572" x2="-6.604" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.921" x2="-1.905" y2="-3.302" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-3.683" x2="1.905" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-3.683" x2="1.905" y2="-3.302" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.921" x2="-1.905" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-3.302" x2="2.794" y2="-3.302" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-3.302" x2="1.905" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-3.302" x2="-2.794" y2="-3.302" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-3.302" x2="-1.905" y2="-3.683" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="1.1938" diameter="2.54" shape="octagon"/>
<pad name="2" x="2.54" y="0" drill="1.1938" diameter="2.54" shape="octagon"/>
<text x="-5.08" y="4.953" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="2.54" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="3.81" y="-3.81" size="1.27" layer="21" ratio="10">5W</text>
</package>
<package name="MPC70-2">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
metal band R, 2W, grid 9 mm&lt;p&gt;
Buerklin</description>
<wire x1="-6.604" y1="-2.032" x2="6.604" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="6.604" y1="-2.032" x2="6.604" y2="2.159" width="0.1524" layer="21"/>
<wire x1="6.604" y1="2.159" x2="-6.604" y2="2.159" width="0.1524" layer="21"/>
<wire x1="-6.604" y1="2.159" x2="-6.604" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-0.635" x2="-1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.397" x2="1.905" y2="-1.397" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.397" x2="1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-0.635" x2="-1.905" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.016" x2="2.794" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.016" x2="1.905" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.016" x2="-2.794" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.016" x2="-1.905" y2="-1.397" width="0.1524" layer="21"/>
<pad name="1" x="-4.445" y="0" drill="1.1176" diameter="2.54" shape="octagon"/>
<pad name="2" x="4.445" y="0" drill="1.1176" diameter="2.54" shape="octagon"/>
<text x="-6.604" y="2.54" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="0" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MPC71-5">
<description>&lt;b&gt;POWER RESISTOR&lt;/b&gt;&lt;p&gt;
metal band R, 5W, grid 9 mm&lt;p&gt;
Buerklin</description>
<wire x1="-6.604" y1="-3.048" x2="6.604" y2="-3.048" width="0.1524" layer="21"/>
<wire x1="6.604" y1="-3.048" x2="6.604" y2="3.048" width="0.1524" layer="21"/>
<wire x1="6.604" y1="3.048" x2="-6.604" y2="3.048" width="0.1524" layer="21"/>
<wire x1="-6.604" y1="3.048" x2="-6.604" y2="-3.048" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-0.889" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.651" x2="1.905" y2="-1.651" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.651" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-0.889" x2="-1.905" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="2.794" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.905" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-2.794" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-1.905" y2="-1.651" width="0.1524" layer="21"/>
<pad name="1" x="-4.445" y="0" drill="1.1176" diameter="2.54" shape="octagon"/>
<pad name="2" x="4.445" y="0" drill="1.1176" diameter="2.54" shape="octagon"/>
<text x="-6.604" y="3.556" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="0" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="AC01">
<description>&lt;b&gt;Cemented Wirewound Resistors&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. acseries.pdf</description>
<wire x1="-5.405" y1="-2.075" x2="5.43" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="5.43" y1="2.075" x2="-5.405" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-5.405" y1="2.075" x2="-5.405" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="5.43" y1="-2.075" x2="5.43" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-8.9" y1="0" x2="-7.62" y2="0" width="0.813" layer="51"/>
<wire x1="7.62" y1="0" x2="8.9" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-8.9" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="8.9" y="0" drill="1.1" diameter="2"/>
<text x="-5.715" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.4064" x2="-5.48" y2="0.4064" layer="21"/>
<rectangle x1="5.505" y1="-0.4064" x2="7.62" y2="0.4064" layer="21"/>
</package>
<package name="AC03">
<description>&lt;b&gt;Cemented Wirewound Resistors&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. acseries.pdf</description>
<wire x1="-6.405" y1="-2.325" x2="6.43" y2="-2.325" width="0.1524" layer="21"/>
<wire x1="6.43" y1="2.325" x2="-6.405" y2="2.325" width="0.1524" layer="21"/>
<wire x1="-6.405" y1="2.325" x2="-6.405" y2="-2.325" width="0.1524" layer="21"/>
<wire x1="6.43" y1="-2.325" x2="6.43" y2="2.325" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0" x2="-7.33" y2="0" width="0.813" layer="51"/>
<wire x1="7.355" y1="0" x2="12.7" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-12.7" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="12.7" y="0" drill="1.1" diameter="2"/>
<text x="-5.715" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.4064" x2="-6.48" y2="0.4064" layer="21"/>
<rectangle x1="6.505" y1="-0.4064" x2="7.62" y2="0.4064" layer="21"/>
</package>
<package name="AC04">
<description>&lt;b&gt;Cemented Wirewound Resistors&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. acseries.pdf</description>
<wire x1="-8.18" y1="-2.65" x2="8.18" y2="-2.65" width="0.1524" layer="21"/>
<wire x1="8.18" y1="2.675" x2="-8.18" y2="2.675" width="0.1524" layer="21"/>
<wire x1="-8.18" y1="2.675" x2="-8.18" y2="-2.65" width="0.1524" layer="21"/>
<wire x1="8.18" y1="-2.65" x2="8.18" y2="2.675" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0" x2="-9.105" y2="0" width="0.813" layer="51"/>
<wire x1="9.105" y1="0" x2="12.7" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-12.7" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="12.7" y="0" drill="1.1" diameter="2"/>
<text x="-6.165" y="3.09" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-10.16" y1="-0.4064" x2="-8.255" y2="0.4064" layer="21"/>
<rectangle x1="8.255" y1="-0.4064" x2="10.16" y2="0.4064" layer="21"/>
</package>
<package name="AC05">
<description>&lt;b&gt;Cemented Wirewound Resistors&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. acseries.pdf</description>
<wire x1="-8.905" y1="-3.675" x2="8.93" y2="-3.675" width="0.1524" layer="21"/>
<wire x1="8.93" y1="3.675" x2="-8.905" y2="3.675" width="0.1524" layer="21"/>
<wire x1="-8.905" y1="3.675" x2="-8.905" y2="-3.675" width="0.1524" layer="21"/>
<wire x1="8.93" y1="-3.675" x2="8.93" y2="3.675" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0" x2="-10.16" y2="0" width="0.813" layer="51"/>
<wire x1="10.16" y1="0" x2="12.7" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-12.7" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="12.7" y="0" drill="1.1" diameter="2"/>
<text x="-7.145" y="4.235" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-10.885" y1="-0.4064" x2="-8.98" y2="0.4064" layer="21"/>
<rectangle x1="9.005" y1="-0.4064" x2="10.91" y2="0.4064" layer="21"/>
</package>
<package name="AC07">
<description>&lt;b&gt;Cemented Wirewound Resistors&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. acseries.pdf</description>
<wire x1="-12.905" y1="-3.675" x2="12.93" y2="-3.675" width="0.1524" layer="21"/>
<wire x1="12.93" y1="3.675" x2="-12.905" y2="3.675" width="0.1524" layer="21"/>
<wire x1="-12.905" y1="3.675" x2="-12.905" y2="-3.675" width="0.1524" layer="21"/>
<wire x1="12.93" y1="-3.675" x2="12.93" y2="3.675" width="0.1524" layer="21"/>
<wire x1="-16.5" y1="0" x2="-14.16" y2="0" width="0.813" layer="51"/>
<wire x1="14.16" y1="0" x2="16.5" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-16.5" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="16.5" y="0" drill="1.1" diameter="2"/>
<text x="-7.07" y="4.135" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-14.885" y1="-0.4064" x2="-12.98" y2="0.4064" layer="21"/>
<rectangle x1="13.005" y1="-0.4064" x2="14.91" y2="0.4064" layer="21"/>
</package>
<package name="AC10">
<description>&lt;b&gt;Cemented Wirewound Resistors&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. acseries.pdf</description>
<wire x1="-21.93" y1="-3.9" x2="21.93" y2="-3.9" width="0.1524" layer="21"/>
<wire x1="21.93" y1="3.9" x2="-21.93" y2="3.9" width="0.1524" layer="21"/>
<wire x1="-21.93" y1="3.9" x2="-21.93" y2="-3.9" width="0.1524" layer="21"/>
<wire x1="21.93" y1="-3.9" x2="21.93" y2="3.9" width="0.1524" layer="21"/>
<wire x1="-25.725" y1="0" x2="-23.185" y2="0" width="0.813" layer="51"/>
<wire x1="23.16" y1="0" x2="25.7" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-25.725" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="25.7" y="0" drill="1.1" diameter="2"/>
<text x="-7.07" y="4.135" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-23.91" y1="-0.4064" x2="-22.005" y2="0.4064" layer="21"/>
<rectangle x1="22.005" y1="-0.4064" x2="23.91" y2="0.4064" layer="21"/>
</package>
<package name="CA0001">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-5.005" y1="-2.075" x2="5.005" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="5.005" y1="2.075" x2="-5.005" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-5.005" y1="2.075" x2="-5.005" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="5.005" y1="-2.075" x2="5.005" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0" x2="-5.93" y2="0" width="0.813" layer="51"/>
<wire x1="5.93" y1="0" x2="7.62" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-7.62" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="7.62" y="0" drill="1.1" diameter="2"/>
<text x="-5.715" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-5.93" y1="-0.4064" x2="-5.08" y2="0.4064" layer="21"/>
<rectangle x1="5.08" y1="-0.4064" x2="5.93" y2="0.4064" layer="21"/>
</package>
<package name="CA0002">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-7.18" y1="-2.075" x2="7.18" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="7.18" y1="2.075" x2="-7.18" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-7.18" y1="2.075" x2="-7.18" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="7.18" y1="-2.075" x2="7.18" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0" x2="-8.89" y2="0" width="0.813" layer="51"/>
<wire x1="8.89" y1="0" x2="10.16" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-10.16" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="10.16" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.89" y1="-0.4064" x2="-7.24" y2="0.4064" layer="21"/>
<rectangle x1="7.24" y1="-0.4064" x2="8.89" y2="0.4064" layer="21"/>
</package>
<package name="CA4050">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-6.28" y1="-1.725" x2="6.28" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="6.28" y1="1.725" x2="-6.28" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-6.28" y1="1.725" x2="-6.28" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="6.28" y1="-1.725" x2="6.28" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="0" x2="-7.62" y2="0" width="0.813" layer="51"/>
<wire x1="7.62" y1="0" x2="8.89" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-8.89" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="8.89" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.4064" x2="-6.35" y2="0.4064" layer="21"/>
<rectangle x1="6.35" y1="-0.4064" x2="7.62" y2="0.4064" layer="21"/>
</package>
<package name="CA4055">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-6.905" y1="-1.7" x2="6.905" y2="-1.7" width="0.1524" layer="21"/>
<wire x1="6.905" y1="1.7" x2="-6.905" y2="1.7" width="0.1524" layer="21"/>
<wire x1="-6.905" y1="1.7" x2="-6.905" y2="-1.7" width="0.1524" layer="21"/>
<wire x1="6.905" y1="-1.7" x2="6.905" y2="1.7" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0" x2="-8.89" y2="0" width="0.813" layer="51"/>
<wire x1="8.89" y1="0" x2="10.16" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-10.16" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="10.16" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.89" y1="-0.4064" x2="-6.985" y2="0.4064" layer="21"/>
<rectangle x1="6.985" y1="-0.4064" x2="8.89" y2="0.4064" layer="21"/>
</package>
<package name="CA4060">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-7.555" y1="-1.725" x2="7.555" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="7.555" y1="1.725" x2="-7.555" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-7.555" y1="1.725" x2="-7.555" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="7.555" y1="-1.725" x2="7.555" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0" x2="-8.89" y2="0" width="0.813" layer="51"/>
<wire x1="8.89" y1="0" x2="10.16" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-10.16" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="10.16" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.89" y1="-0.4064" x2="-7.62" y2="0.4064" layer="21"/>
<rectangle x1="7.62" y1="-0.4064" x2="8.89" y2="0.4064" layer="21"/>
</package>
<package name="CA4070">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-8.805" y1="-1.725" x2="8.805" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="8.805" y1="1.725" x2="-8.805" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-8.805" y1="1.725" x2="-8.805" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="8.805" y1="-1.725" x2="8.805" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="0" x2="-10.14" y2="0" width="0.813" layer="51"/>
<wire x1="10.14" y1="0" x2="11.43" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-11.43" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="11.43" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-10.14" y1="-0.4064" x2="-8.87" y2="0.4064" layer="21"/>
<rectangle x1="8.87" y1="-0.4064" x2="10.14" y2="0.4064" layer="21"/>
</package>
<package name="CA4080">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-10.075" y1="-1.725" x2="10.075" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="10.075" y1="1.725" x2="-10.075" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-10.075" y1="1.725" x2="-10.075" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="10.075" y1="-1.725" x2="10.075" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0" x2="-11.41" y2="0" width="0.813" layer="51"/>
<wire x1="11.41" y1="0" x2="12.7" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-12.7" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="12.7" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-11.41" y1="-0.4064" x2="-10.14" y2="0.4064" layer="21"/>
<rectangle x1="10.14" y1="-0.4064" x2="11.41" y2="0.4064" layer="21"/>
</package>
<package name="CA4090">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-11.345" y1="-1.725" x2="11.345" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="11.345" y1="1.725" x2="-11.345" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-11.345" y1="1.725" x2="-11.345" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="11.345" y1="-1.725" x2="11.345" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="0" x2="-12.68" y2="0" width="0.813" layer="51"/>
<wire x1="12.68" y1="0" x2="13.97" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-13.97" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="13.97" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-12.68" y1="-0.4064" x2="-11.41" y2="0.4064" layer="21"/>
<rectangle x1="11.41" y1="-0.4064" x2="12.68" y2="0.4064" layer="21"/>
</package>
<package name="CA4100">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-12.615" y1="-1.725" x2="12.615" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="12.615" y1="1.725" x2="-12.615" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-12.615" y1="1.725" x2="-12.615" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="12.615" y1="-1.725" x2="12.615" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="0" x2="-13.95" y2="0" width="0.813" layer="51"/>
<wire x1="13.95" y1="0" x2="15.24" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-15.24" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="15.24" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-13.95" y1="-0.4064" x2="-12.68" y2="0.4064" layer="21"/>
<rectangle x1="12.68" y1="-0.4064" x2="13.95" y2="0.4064" layer="21"/>
</package>
<package name="CA4150">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-18.965" y1="-1.725" x2="18.965" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="18.965" y1="1.725" x2="-18.965" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-18.965" y1="1.725" x2="-18.965" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="18.965" y1="-1.725" x2="18.965" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="0" x2="-20.3" y2="0" width="0.813" layer="51"/>
<wire x1="20.3" y1="0" x2="21.59" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-21.59" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="21.59" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-20.3" y1="-0.4064" x2="-19.03" y2="0.4064" layer="21"/>
<rectangle x1="19.03" y1="-0.4064" x2="20.3" y2="0.4064" layer="21"/>
</package>
<package name="CA4200">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-25.315" y1="-1.725" x2="25.315" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="25.315" y1="1.725" x2="-25.315" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-25.315" y1="1.725" x2="-25.315" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="25.315" y1="-1.725" x2="25.315" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-27.94" y1="0" x2="-26.65" y2="0" width="0.813" layer="51"/>
<wire x1="26.65" y1="0" x2="27.94" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-27.94" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="27.94" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-26.65" y1="-0.4064" x2="-25.38" y2="0.4064" layer="21"/>
<rectangle x1="25.38" y1="-0.4064" x2="26.65" y2="0.4064" layer="21"/>
</package>
<package name="CA4220">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-27.855" y1="-1.725" x2="27.855" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="27.855" y1="1.725" x2="-27.855" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-27.855" y1="1.725" x2="-27.855" y2="-1.725" width="0.1524" layer="21"/>
<wire x1="27.855" y1="-1.725" x2="27.855" y2="1.725" width="0.1524" layer="21"/>
<wire x1="-30.48" y1="0" x2="-29.19" y2="0" width="0.813" layer="51"/>
<wire x1="29.19" y1="0" x2="30.48" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-30.48" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="30.48" y="0" drill="1.1" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-29.19" y1="-0.4064" x2="-27.92" y2="0.4064" layer="21"/>
<rectangle x1="27.92" y1="-0.4064" x2="29.19" y2="0.4064" layer="21"/>
</package>
<package name="CA5050">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-6.28" y1="-2.075" x2="6.28" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="6.28" y1="2.075" x2="-6.28" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-6.28" y1="2.075" x2="-6.28" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="6.28" y1="-2.075" x2="6.28" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="0" x2="-7.62" y2="0" width="0.813" layer="51"/>
<wire x1="7.62" y1="0" x2="9.525" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-9.525" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="9.525" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.4064" x2="-6.35" y2="0.4064" layer="21"/>
<rectangle x1="6.35" y1="-0.4064" x2="7.62" y2="0.4064" layer="21"/>
</package>
<package name="CA5055">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-6.905" y1="-2.075" x2="6.905" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="6.905" y1="2.075" x2="-6.905" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-6.905" y1="2.075" x2="-6.905" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="6.905" y1="-2.075" x2="6.905" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0" x2="-8.245" y2="0" width="0.813" layer="51"/>
<wire x1="8.245" y1="0" x2="10.16" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-10.16" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="10.16" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.245" y1="-0.4064" x2="-6.975" y2="0.4064" layer="21"/>
<rectangle x1="6.975" y1="-0.4064" x2="8.245" y2="0.4064" layer="21"/>
</package>
<package name="CA5060">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-7.54" y1="-2.075" x2="7.54" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="7.54" y1="2.075" x2="-7.54" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-7.54" y1="2.075" x2="-7.54" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="7.54" y1="-2.075" x2="7.54" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="0" x2="-8.88" y2="0" width="0.813" layer="51"/>
<wire x1="8.88" y1="0" x2="10.795" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-10.795" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="10.795" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.88" y1="-0.4064" x2="-7.61" y2="0.4064" layer="21"/>
<rectangle x1="7.61" y1="-0.4064" x2="8.88" y2="0.4064" layer="21"/>
</package>
<package name="CA5070">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-8.81" y1="-2.075" x2="8.81" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="8.81" y1="2.075" x2="-8.81" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-8.81" y1="2.075" x2="-8.81" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="8.81" y1="-2.075" x2="8.81" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="0" x2="-10.15" y2="0" width="0.813" layer="51"/>
<wire x1="10.15" y1="0" x2="12.065" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-12.065" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="12.065" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-10.15" y1="-0.4064" x2="-8.88" y2="0.4064" layer="21"/>
<rectangle x1="8.88" y1="-0.4064" x2="10.15" y2="0.4064" layer="21"/>
</package>
<package name="CA5080">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-10.08" y1="-2.075" x2="10.08" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="10.08" y1="2.075" x2="-10.08" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-10.08" y1="2.075" x2="-10.08" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="10.08" y1="-2.075" x2="10.08" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="0" x2="-11.42" y2="0" width="0.813" layer="51"/>
<wire x1="11.42" y1="0" x2="13.335" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-13.335" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="13.335" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-11.42" y1="-0.4064" x2="-10.15" y2="0.4064" layer="21"/>
<rectangle x1="10.15" y1="-0.4064" x2="11.42" y2="0.4064" layer="21"/>
</package>
<package name="CA5090">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-11.35" y1="-2.075" x2="11.35" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="11.35" y1="2.075" x2="-11.35" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-11.35" y1="2.075" x2="-11.35" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="11.35" y1="-2.075" x2="11.35" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="0" x2="-12.69" y2="0" width="0.813" layer="51"/>
<wire x1="12.69" y1="0" x2="14.605" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-14.605" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="14.605" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-12.69" y1="-0.4064" x2="-11.42" y2="0.4064" layer="21"/>
<rectangle x1="11.42" y1="-0.4064" x2="12.69" y2="0.4064" layer="21"/>
</package>
<package name="CA5100">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-12.62" y1="-2.075" x2="12.62" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="12.62" y1="2.075" x2="-12.62" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-12.62" y1="2.075" x2="-12.62" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="12.62" y1="-2.075" x2="12.62" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="0" x2="-13.96" y2="0" width="0.813" layer="51"/>
<wire x1="13.96" y1="0" x2="15.875" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-15.875" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="15.875" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-13.96" y1="-0.4064" x2="-12.69" y2="0.4064" layer="21"/>
<rectangle x1="12.69" y1="-0.4064" x2="13.96" y2="0.4064" layer="21"/>
</package>
<package name="CA5150">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-18.97" y1="-2.075" x2="18.97" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="18.97" y1="2.075" x2="-18.97" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-18.97" y1="2.075" x2="-18.97" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="18.97" y1="-2.075" x2="18.97" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-22.225" y1="0" x2="-20.31" y2="0" width="0.813" layer="51"/>
<wire x1="20.31" y1="0" x2="22.225" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-22.225" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="22.225" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-20.31" y1="-0.4064" x2="-19.04" y2="0.4064" layer="21"/>
<rectangle x1="19.04" y1="-0.4064" x2="20.31" y2="0.4064" layer="21"/>
</package>
<package name="CA5200">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-25.32" y1="-2.075" x2="25.32" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="25.32" y1="2.075" x2="-25.32" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-25.32" y1="2.075" x2="-25.32" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="25.32" y1="-2.075" x2="25.32" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-28.575" y1="0" x2="-26.66" y2="0" width="0.813" layer="51"/>
<wire x1="26.66" y1="0" x2="28.575" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-28.575" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="28.575" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-26.66" y1="-0.4064" x2="-25.39" y2="0.4064" layer="21"/>
<rectangle x1="25.39" y1="-0.4064" x2="26.66" y2="0.4064" layer="21"/>
</package>
<package name="CA5220">
<description>&lt;b&gt;Wirewound Resistors, Commercial Power, Axial Lead&lt;/b&gt;&lt;p&gt;
Source: Vishay Dale .. 30214.pdf</description>
<wire x1="-27.86" y1="-2.075" x2="27.86" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="27.86" y1="2.075" x2="-27.86" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-27.86" y1="2.075" x2="-27.86" y2="-2.075" width="0.1524" layer="21"/>
<wire x1="27.86" y1="-2.075" x2="27.86" y2="2.075" width="0.1524" layer="21"/>
<wire x1="-31.115" y1="0" x2="-29.2" y2="0" width="0.813" layer="51"/>
<wire x1="29.2" y1="0" x2="31.115" y2="0" width="0.813" layer="51"/>
<pad name="1" x="-31.115" y="0" drill="1.2" diameter="2"/>
<pad name="2" x="31.115" y="0" drill="1.2" diameter="2"/>
<text x="-6.35" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-29.2" y1="-0.4064" x2="-27.93" y2="0.4064" layer="21"/>
<rectangle x1="27.93" y1="-0.4064" x2="29.2" y2="0.4064" layer="21"/>
</package>
<package name="HPS523">
<description>&lt;b&gt;High Ohmic Value (up to 1.5 G?), High Power Resistors&lt;/b&gt;&lt;p&gt;
(up to 10 W at 25 °C) Thick Film Technology&lt;br&gt;
Source: Vishay Dale .. hps.pdf</description>
<wire x1="-11.43" y1="-2.425" x2="11.43" y2="-2.425" width="0.1524" layer="21"/>
<wire x1="11.43" y1="2.425" x2="-11.43" y2="2.425" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="2.425" x2="-11.43" y2="-2.425" width="0.1524" layer="21"/>
<wire x1="11.43" y1="-2.425" x2="11.43" y2="2.425" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="0" x2="-12.06" y2="0" width="0.8" layer="51"/>
<wire x1="12.06" y1="0" x2="13.97" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-13.97" y="0" drill="1.1" diameter="1.7"/>
<pad name="2" x="13.97" y="0" drill="1.1" diameter="1.7"/>
<text x="-6.95" y="3.075" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.47" y="-0.835" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-12.06" y1="-0.4" x2="-11.505" y2="0.4" layer="21"/>
<rectangle x1="11.505" y1="-0.4" x2="12.06" y2="0.4" layer="21"/>
</package>
<package name="HPS58">
<description>&lt;b&gt;High Ohmic Value (up to 1.5 G?), High Power Resistors&lt;/b&gt;&lt;p&gt;
(up to 10 W at 25 °C) Thick Film Technology&lt;br&gt;
Source: Vishay Dale .. hps.pdf</description>
<wire x1="-3.18" y1="-1.125" x2="3.18" y2="-1.125" width="0.1524" layer="21"/>
<wire x1="3.18" y1="1.125" x2="-3.18" y2="1.125" width="0.1524" layer="21"/>
<wire x1="-3.18" y1="1.125" x2="-3.18" y2="-1.125" width="0.1524" layer="21"/>
<wire x1="3.18" y1="-1.125" x2="3.18" y2="1.125" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0" x2="-3.81" y2="0" width="0.6" layer="51"/>
<wire x1="3.81" y1="0" x2="5.08" y2="0" width="0.6" layer="51"/>
<pad name="1" x="-5.08" y="0" drill="0.9" diameter="1.5"/>
<pad name="2" x="5.08" y="0" drill="0.9" diameter="1.5"/>
<text x="-3.175" y="1.27" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.845" y="-0.835" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.81" y1="-0.3" x2="-3.255" y2="0.3" layer="21"/>
<rectangle x1="3.255" y1="-0.3" x2="3.81" y2="0.3" layer="21"/>
</package>
<package name="HPS63">
<description>&lt;b&gt;High Ohmic Value (up to 1.5 G?), High Power Resistors&lt;/b&gt;&lt;p&gt;
(up to 10 W at 25 °C) Thick Film Technology&lt;br&gt;
Source: Vishay Dale .. hps.pdf</description>
<wire x1="-4.93" y1="-1.125" x2="4.93" y2="-1.125" width="0.1524" layer="21"/>
<wire x1="4.93" y1="1.125" x2="-4.93" y2="1.125" width="0.1524" layer="21"/>
<wire x1="-4.93" y1="1.125" x2="-4.93" y2="-1.125" width="0.1524" layer="21"/>
<wire x1="4.93" y1="-1.125" x2="4.93" y2="1.125" width="0.1524" layer="21"/>
<wire x1="-6.83" y1="0" x2="-5.56" y2="0" width="0.6" layer="51"/>
<wire x1="5.56" y1="0" x2="6.83" y2="0" width="0.6" layer="51"/>
<pad name="1" x="-6.83" y="0" drill="0.9" diameter="1.5"/>
<pad name="2" x="6.83" y="0" drill="0.9" diameter="1.5"/>
<text x="-4.925" y="1.27" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.595" y="-0.835" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-5.56" y1="-0.3" x2="-5.005" y2="0.3" layer="21"/>
<rectangle x1="5.005" y1="-0.3" x2="5.56" y2="0.3" layer="21"/>
</package>
<package name="HPS68">
<description>&lt;b&gt;High Ohmic Value (up to 1.5 G?), High Power Resistors&lt;/b&gt;&lt;p&gt;
(up to 10 W at 25 °C) Thick Film Technology&lt;br&gt;
Source: Vishay Dale .. hps.pdf</description>
<wire x1="-7.43" y1="-2.725" x2="7.43" y2="-2.725" width="0.1524" layer="21"/>
<wire x1="7.43" y1="2.725" x2="-7.43" y2="2.725" width="0.1524" layer="21"/>
<wire x1="-7.43" y1="2.725" x2="-7.43" y2="-2.725" width="0.1524" layer="21"/>
<wire x1="7.43" y1="-2.725" x2="7.43" y2="2.725" width="0.1524" layer="21"/>
<wire x1="-9.33" y1="0" x2="-8.06" y2="0" width="0.8" layer="51"/>
<wire x1="8.06" y1="0" x2="9.33" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-9.33" y="0" drill="1.1" diameter="1.7"/>
<pad name="2" x="9.33" y="0" drill="1.1" diameter="1.7"/>
<text x="-6.95" y="3.075" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.47" y="-0.835" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.06" y1="-0.4" x2="-7.505" y2="0.4" layer="21"/>
<rectangle x1="7.505" y1="-0.4" x2="8.06" y2="0.4" layer="21"/>
</package>
<package name="HPS923">
<description>&lt;b&gt;High Ohmic Value (up to 1.5 G?), High Power Resistors&lt;/b&gt;&lt;p&gt;
(up to 10 W at 25 °C) Thick Film Technology&lt;br&gt;
Source: Vishay Dale .. hps.pdf</description>
<wire x1="-11.43" y1="-4.425" x2="11.43" y2="-4.425" width="0.1524" layer="21"/>
<wire x1="11.43" y1="4.425" x2="-11.43" y2="4.425" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="4.425" x2="-11.43" y2="-4.425" width="0.1524" layer="21"/>
<wire x1="11.43" y1="-4.425" x2="11.43" y2="4.425" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="0" x2="-12.06" y2="0" width="0.8" layer="51"/>
<wire x1="12.06" y1="0" x2="13.97" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-13.97" y="0" drill="1.1" diameter="1.7"/>
<pad name="2" x="13.97" y="0" drill="1.1" diameter="1.7"/>
<text x="-6.95" y="5.075" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.47" y="-0.835" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-12.06" y1="-0.4" x2="-11.505" y2="0.4" layer="21"/>
<rectangle x1="11.505" y1="-0.4" x2="12.06" y2="0.4" layer="21"/>
</package>
<package name="HPS932">
<description>&lt;b&gt;High Ohmic Value (up to 1.5 G?), High Power Resistors&lt;/b&gt;&lt;p&gt;
(up to 10 W at 25 °C) Thick Film Technology&lt;br&gt;
Source: Vishay Dale .. hps.pdf</description>
<wire x1="-15.93" y1="-4.425" x2="15.93" y2="-4.425" width="0.1524" layer="21"/>
<wire x1="15.93" y1="4.425" x2="-15.93" y2="4.425" width="0.1524" layer="21"/>
<wire x1="-15.93" y1="4.425" x2="-15.93" y2="-4.425" width="0.1524" layer="21"/>
<wire x1="15.93" y1="-4.425" x2="15.93" y2="4.425" width="0.1524" layer="21"/>
<wire x1="-18.47" y1="0" x2="-16.56" y2="0" width="0.8" layer="51"/>
<wire x1="16.56" y1="0" x2="18.47" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-18.47" y="0" drill="1.1" diameter="1.7"/>
<pad name="2" x="18.47" y="0" drill="1.1" diameter="1.7"/>
<text x="-6.95" y="5.075" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.47" y="-0.835" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-16.56" y1="-0.4" x2="-16.005" y2="0.4" layer="21"/>
<rectangle x1="16.005" y1="-0.4" x2="16.56" y2="0.4" layer="21"/>
</package>
<package name="HPS947">
<description>&lt;b&gt;High Ohmic Value (up to 1.5 G?), High Power Resistors&lt;/b&gt;&lt;p&gt;
(up to 10 W at 25 °C) Thick Film Technology&lt;br&gt;
Source: Vishay Dale .. hps.pdf</description>
<wire x1="-23.43" y1="-4.425" x2="23.43" y2="-4.425" width="0.1524" layer="21"/>
<wire x1="23.43" y1="4.425" x2="-23.43" y2="4.425" width="0.1524" layer="21"/>
<wire x1="-23.43" y1="4.425" x2="-23.43" y2="-4.425" width="0.1524" layer="21"/>
<wire x1="23.43" y1="-4.425" x2="23.43" y2="4.425" width="0.1524" layer="21"/>
<wire x1="-25.97" y1="0" x2="-24.06" y2="0" width="0.8" layer="51"/>
<wire x1="24.06" y1="0" x2="25.97" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-25.97" y="0" drill="1.1" diameter="1.7"/>
<pad name="2" x="25.97" y="0" drill="1.1" diameter="1.7"/>
<text x="-6.95" y="5.075" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.47" y="-0.835" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-24.06" y1="-0.4" x2="-23.505" y2="0.4" layer="21"/>
<rectangle x1="23.505" y1="-0.4" x2="24.06" y2="0.4" layer="21"/>
</package>
<package name="RS002">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-7.855" y1="-3.1" x2="7.855" y2="-3.1" width="0.1524" layer="21"/>
<wire x1="7.855" y1="3.1" x2="-7.855" y2="3.1" width="0.1524" layer="21"/>
<wire x1="-7.855" y1="3.1" x2="-7.855" y2="-3.1" width="0.1524" layer="21"/>
<wire x1="7.855" y1="-3.1" x2="7.855" y2="3.1" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="0" x2="-8.89" y2="0" width="1" layer="51"/>
<wire x1="8.89" y1="0" x2="10.795" y2="0" width="1" layer="51"/>
<pad name="1" x="-10.795" y="0" drill="1.4" diameter="2.2"/>
<pad name="2" x="10.795" y="0" drill="1.4" diameter="2.2" rot="R90"/>
<text x="-7.62" y="3.81" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.985" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.89" y1="-0.5" x2="-7.93" y2="0.5" layer="21"/>
<rectangle x1="7.93" y1="-0.5" x2="8.89" y2="0.5" layer="21"/>
</package>
<package name="RS007">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-15.405" y1="-3.875" x2="15.405" y2="-3.875" width="0.1524" layer="21"/>
<wire x1="15.405" y1="3.875" x2="-15.405" y2="3.875" width="0.1524" layer="21"/>
<wire x1="-15.405" y1="3.875" x2="-15.405" y2="-3.875" width="0.1524" layer="21"/>
<wire x1="15.405" y1="-3.875" x2="15.405" y2="3.875" width="0.1524" layer="21"/>
<wire x1="-18.98" y1="0" x2="-16.745" y2="0" width="1" layer="51"/>
<wire x1="16.745" y1="0" x2="18.98" y2="0" width="1" layer="51"/>
<pad name="1" x="-18.98" y="0" drill="1.3" diameter="2.2"/>
<pad name="2" x="18.98" y="0" drill="1.3" diameter="2.2" rot="R90"/>
<text x="-10.16" y="4.445" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.41" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-16.745" y1="-0.5" x2="-15.48" y2="0.5" layer="21"/>
<rectangle x1="15.48" y1="-0.5" x2="16.745" y2="0.5" layer="21"/>
</package>
<package name="RS01A">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-5.08" y1="-1.125" x2="5.08" y2="-1.125" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.125" x2="-5.08" y2="1.125" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.125" x2="-5.08" y2="-1.125" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.125" x2="5.08" y2="1.125" width="0.1524" layer="21"/>
<wire x1="-6.915" y1="0" x2="-5.785" y2="0" width="0.5" layer="51"/>
<wire x1="5.715" y1="0" x2="6.915" y2="0" width="0.5" layer="51"/>
<pad name="1" x="-6.915" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="6.915" y="0" drill="0.8" diameter="1.4" rot="R90"/>
<text x="-4.375" y="1.27" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.175" y="-3.175" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-5.785" y1="-0.25" x2="-5.155" y2="0.25" layer="21"/>
<rectangle x1="5.155" y1="-0.25" x2="5.785" y2="0.25" layer="21"/>
</package>
<package name="RS01M">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-3.555" y1="-1.325" x2="3.555" y2="-1.325" width="0.1524" layer="21"/>
<wire x1="3.555" y1="1.325" x2="-3.555" y2="1.325" width="0.1524" layer="21"/>
<wire x1="-3.555" y1="1.325" x2="-3.555" y2="-1.325" width="0.1524" layer="21"/>
<wire x1="3.555" y1="-1.325" x2="3.555" y2="1.325" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="0" x2="-4.445" y2="0" width="0.5" layer="51"/>
<wire x1="4.445" y1="0" x2="5.715" y2="0" width="0.5" layer="51"/>
<pad name="1" x="-5.715" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="5.715" y="0" drill="0.8" diameter="1.4" rot="R90"/>
<text x="-3.175" y="1.905" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.175" y="-3.81" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-4.445" y1="-0.25" x2="-3.63" y2="0.25" layer="21"/>
<rectangle x1="3.63" y1="-0.25" x2="4.445" y2="0.25" layer="21"/>
</package>
<package name="RS02B">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-7.03" y1="-2.3" x2="7.03" y2="-2.3" width="0.1524" layer="21"/>
<wire x1="7.03" y1="2.3" x2="-7.03" y2="2.3" width="0.1524" layer="21"/>
<wire x1="-7.03" y1="2.3" x2="-7.03" y2="-2.3" width="0.1524" layer="21"/>
<wire x1="7.03" y1="-2.3" x2="7.03" y2="2.3" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0" x2="-8.37" y2="0" width="0.8" layer="51"/>
<wire x1="8.37" y1="0" x2="10.16" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-10.16" y="0" drill="1.1" diameter="2.2"/>
<pad name="2" x="10.16" y="0" drill="1.1" diameter="2.2" rot="R90"/>
<text x="-5.715" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.41" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.37" y1="-0.4" x2="-7.105" y2="0.4" layer="21"/>
<rectangle x1="7.105" y1="-0.4" x2="8.37" y2="0.4" layer="21"/>
</package>
<package name="RS02C">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-6.28" y1="-2.7" x2="6.28" y2="-2.7" width="0.1524" layer="21"/>
<wire x1="6.28" y1="2.7" x2="-6.28" y2="2.7" width="0.1524" layer="21"/>
<wire x1="-6.28" y1="2.7" x2="-6.28" y2="-2.7" width="0.1524" layer="21"/>
<wire x1="6.28" y1="-2.7" x2="6.28" y2="2.7" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="0" x2="-7.62" y2="0" width="1" layer="51"/>
<wire x1="7.62" y1="0" x2="8.89" y2="0" width="1" layer="51"/>
<pad name="1" x="-8.89" y="0" drill="1.3" diameter="2.2"/>
<pad name="2" x="8.89" y="0" drill="1.3" diameter="2.2" rot="R90"/>
<text x="-6.35" y="3.175" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.41" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.5" x2="-6.355" y2="0.5" layer="21"/>
<rectangle x1="6.355" y1="-0.5" x2="7.62" y2="0.5" layer="21"/>
</package>
<package name="RS02C_17-23">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-6.28" y1="-2.7" x2="6.28" y2="-2.7" width="0.1524" layer="21"/>
<wire x1="6.28" y1="2.7" x2="-6.28" y2="2.7" width="0.1524" layer="21"/>
<wire x1="-6.28" y1="2.7" x2="-6.28" y2="-2.7" width="0.1524" layer="21"/>
<wire x1="6.28" y1="-2.7" x2="6.28" y2="2.7" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="0" x2="-7.62" y2="0" width="0.8" layer="51"/>
<wire x1="7.62" y1="0" x2="8.89" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-8.89" y="0" drill="1.1" diameter="2.2"/>
<pad name="2" x="8.89" y="0" drill="1.1" diameter="2.2" rot="R90"/>
<text x="-6.35" y="3.175" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.41" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.4" x2="-6.355" y2="0.4" layer="21"/>
<rectangle x1="6.355" y1="-0.4" x2="7.62" y2="0.4" layer="21"/>
</package>
<package name="RS02M">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-6.28" y1="-2.275" x2="6.28" y2="-2.275" width="0.1524" layer="21"/>
<wire x1="6.28" y1="2.25" x2="-6.28" y2="2.25" width="0.1524" layer="21"/>
<wire x1="-6.28" y1="2.25" x2="-6.28" y2="-2.275" width="0.1524" layer="21"/>
<wire x1="6.28" y1="-2.275" x2="6.28" y2="2.25" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="0" x2="-7.62" y2="0" width="0.8" layer="51"/>
<wire x1="7.62" y1="0" x2="9.525" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-9.525" y="0" drill="1.1" diameter="2.2"/>
<pad name="2" x="9.525" y="0" drill="1.1" diameter="2.2" rot="R90"/>
<text x="-5.715" y="2.54" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.41" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.4" x2="-6.355" y2="0.4" layer="21"/>
<rectangle x1="6.355" y1="-0.4" x2="7.62" y2="0.4" layer="21"/>
</package>
<package name="RS05_69-70">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-11.03" y1="-3.875" x2="11.03" y2="-3.875" width="0.1524" layer="21"/>
<wire x1="11.03" y1="3.875" x2="-11.03" y2="3.875" width="0.1524" layer="21"/>
<wire x1="-11.03" y1="3.875" x2="-11.03" y2="-3.875" width="0.1524" layer="21"/>
<wire x1="11.03" y1="-3.875" x2="11.03" y2="3.875" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="0" x2="-12.37" y2="0" width="1" layer="51"/>
<wire x1="12.37" y1="0" x2="14.605" y2="0" width="1" layer="51"/>
<pad name="1" x="-14.605" y="0" drill="1.3" diameter="2.2"/>
<pad name="2" x="14.605" y="0" drill="1.3" diameter="2.2" rot="R90"/>
<text x="-10.16" y="4.445" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.41" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-12.37" y1="-0.5" x2="-11.105" y2="0.5" layer="21"/>
<rectangle x1="11.105" y1="-0.5" x2="12.37" y2="0.5" layer="21"/>
</package>
<package name="RS1/2">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-3.88" y1="-0.925" x2="3.88" y2="-0.925" width="0.1524" layer="21"/>
<wire x1="3.88" y1="0.925" x2="-3.88" y2="0.925" width="0.1524" layer="21"/>
<wire x1="-3.88" y1="0.925" x2="-3.88" y2="-0.925" width="0.1524" layer="21"/>
<wire x1="3.88" y1="-0.925" x2="3.88" y2="0.925" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="0" x2="-4.585" y2="0" width="0.5" layer="51"/>
<wire x1="4.515" y1="0" x2="5.715" y2="0" width="0.5" layer="51"/>
<pad name="1" x="-5.715" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="5.715" y="0" drill="0.8" diameter="1.4" rot="R90"/>
<text x="-3.175" y="1.27" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.175" y="-3.175" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-4.585" y1="-0.25" x2="-3.955" y2="0.25" layer="21"/>
<rectangle x1="3.955" y1="-0.25" x2="4.585" y2="0.25" layer="21"/>
</package>
<package name="RS1/4">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-3.105" y1="-1" x2="3.105" y2="-1" width="0.1524" layer="21"/>
<wire x1="3.105" y1="1" x2="-3.105" y2="1" width="0.1524" layer="21"/>
<wire x1="-3.105" y1="1" x2="-3.105" y2="-1" width="0.1524" layer="21"/>
<wire x1="3.105" y1="-1" x2="3.105" y2="1" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0" x2="-3.81" y2="0" width="0.5" layer="51"/>
<wire x1="3.74" y1="0" x2="5.08" y2="0" width="0.5" layer="51"/>
<pad name="1" x="-5.08" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="5.08" y="0" drill="0.8" diameter="1.4" rot="R90"/>
<text x="-3.175" y="1.27" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.175" y="-3.175" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.81" y1="-0.25" x2="-3.18" y2="0.25" layer="21"/>
<rectangle x1="3.18" y1="-0.25" x2="3.81" y2="0.25" layer="21"/>
</package>
<package name="RS1/8">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-1.905" y1="-0.75" x2="1.905" y2="-0.75" width="0.1524" layer="21"/>
<wire x1="1.905" y1="0.75" x2="-1.905" y2="0.75" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="0.75" x2="-1.905" y2="-0.75" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-0.75" x2="1.905" y2="0.75" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0" x2="-2.54" y2="0" width="0.5" layer="51"/>
<wire x1="2.54" y1="0" x2="3.81" y2="0" width="0.5" layer="51"/>
<pad name="1" x="-3.81" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="3.81" y="0" drill="0.8" diameter="1.4"/>
<text x="-2.54" y="1.27" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-2.54" y1="-0.25" x2="-1.98" y2="0.25" layer="21"/>
<rectangle x1="1.98" y1="-0.25" x2="2.54" y2="0.25" layer="21"/>
</package>
<package name="RS10_38-39">
<description>&lt;b&gt;Wirewound Resistors, Military, MIL-PRF-26 Qualified&lt;/b&gt;&lt;p&gt;
Type RW, Precision Power, Silicone Coated&lt;br&gt;
Source: Vishay Dale .. rsns.pdf</description>
<wire x1="-22.53" y1="-4.675" x2="22.53" y2="-4.675" width="0.1524" layer="21"/>
<wire x1="22.53" y1="4.675" x2="-22.53" y2="4.675" width="0.1524" layer="21"/>
<wire x1="-22.53" y1="4.675" x2="-22.53" y2="-4.675" width="0.1524" layer="21"/>
<wire x1="22.53" y1="-4.675" x2="22.53" y2="4.675" width="0.1524" layer="21"/>
<wire x1="-26.035" y1="0" x2="-23.87" y2="0" width="1" layer="51"/>
<wire x1="23.87" y1="0" x2="26.035" y2="0" width="1" layer="51"/>
<pad name="1" x="-26.035" y="0" drill="1.3" diameter="2.2"/>
<pad name="2" x="26.035" y="0" drill="1.3" diameter="2.2" rot="R90"/>
<text x="-18.415" y="5.08" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.41" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-23.87" y1="-0.5" x2="-22.605" y2="0.5" layer="21"/>
<rectangle x1="22.605" y1="-0.5" x2="23.87" y2="0.5" layer="21"/>
</package>
<package name="RWM10X45">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-22.78" y1="-4.625" x2="22.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="22.78" y1="4.625" x2="-22.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-22.78" y1="4.625" x2="-22.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="22.78" y1="-4.625" x2="22.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-25.74" y1="0" x2="-24.47" y2="0" width="0.8" layer="51"/>
<wire x1="24.47" y1="0" x2="25.74" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-25.74" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="25.74" y="0" drill="1.1" diameter="2"/>
<text x="-22.565" y="5.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-24.47" y1="-0.4" x2="-22.855" y2="0.4" layer="21"/>
<rectangle x1="22.855" y1="-0.4" x2="24.47" y2="0.4" layer="21"/>
</package>
<package name="RWM10X64">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-31.78" y1="-4.625" x2="31.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="31.78" y1="4.625" x2="-31.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-31.78" y1="4.625" x2="-31.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="31.78" y1="-4.625" x2="31.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-34.74" y1="0" x2="-33.47" y2="0" width="0.8" layer="51"/>
<wire x1="33.47" y1="0" x2="34.74" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-34.74" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="34.74" y="0" drill="1.1" diameter="2"/>
<text x="-31.565" y="5.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-33.47" y1="-0.4" x2="-31.855" y2="0.4" layer="21"/>
<rectangle x1="31.855" y1="-0.4" x2="33.47" y2="0.4" layer="21"/>
</package>
<package name="RWM10X65">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-31.78" y1="-4.625" x2="31.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="31.78" y1="4.625" x2="-31.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-31.78" y1="4.625" x2="-31.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="31.78" y1="-4.625" x2="31.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-34.74" y1="0" x2="-33.47" y2="0" width="0.8" layer="51"/>
<wire x1="33.47" y1="0" x2="34.74" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-34.74" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="34.74" y="0" drill="1.1" diameter="2"/>
<text x="-31.565" y="5.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-33.47" y1="-0.4" x2="-31.855" y2="0.4" layer="21"/>
<rectangle x1="31.855" y1="-0.4" x2="33.47" y2="0.4" layer="21"/>
</package>
<package name="RWM4X10">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-5.93" y1="-2.675" x2="5.93" y2="-2.675" width="0.1524" layer="21"/>
<wire x1="5.93" y1="2.675" x2="-5.93" y2="2.675" width="0.1524" layer="21"/>
<wire x1="-5.93" y1="2.675" x2="-5.93" y2="-2.675" width="0.1524" layer="21"/>
<wire x1="5.93" y1="-2.675" x2="5.93" y2="2.675" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="0" x2="-7.62" y2="0" width="0.8" layer="51"/>
<wire x1="7.62" y1="0" x2="8.89" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-8.89" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="8.89" y="0" drill="1.1" diameter="2"/>
<text x="-5.715" y="3.175" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-0.4" x2="-6.005" y2="0.4" layer="21"/>
<rectangle x1="6.005" y1="-0.4" x2="7.62" y2="0.4" layer="21"/>
</package>
<package name="RWM4X22">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-10.98" y1="-2.675" x2="10.98" y2="-2.675" width="0.1524" layer="21"/>
<wire x1="10.98" y1="2.675" x2="-10.98" y2="2.675" width="0.1524" layer="21"/>
<wire x1="-10.98" y1="2.675" x2="-10.98" y2="-2.675" width="0.1524" layer="21"/>
<wire x1="10.98" y1="-2.675" x2="10.98" y2="2.675" width="0.1524" layer="21"/>
<wire x1="-13.94" y1="0" x2="-12.67" y2="0" width="0.8" layer="51"/>
<wire x1="12.67" y1="0" x2="13.94" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-13.94" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="13.94" y="0" drill="1.1" diameter="2"/>
<text x="-10.765" y="3.175" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-12.67" y1="-0.4" x2="-11.055" y2="0.4" layer="21"/>
<rectangle x1="11.055" y1="-0.4" x2="12.67" y2="0.4" layer="21"/>
</package>
<package name="RWM5X26">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-12.28" y1="-3.625" x2="12.28" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="12.28" y1="3.625" x2="-12.28" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-12.28" y1="3.625" x2="-12.28" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="12.28" y1="-3.625" x2="12.28" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="0" x2="-13.97" y2="0" width="0.8" layer="51"/>
<wire x1="13.97" y1="0" x2="15.24" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-15.24" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="15.24" y="0" drill="1.1" diameter="2"/>
<text x="-12.065" y="4.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-13.97" y1="-0.4" x2="-12.355" y2="0.4" layer="21"/>
<rectangle x1="12.355" y1="-0.4" x2="13.97" y2="0.4" layer="21"/>
</package>
<package name="RWM6X22">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-8.93" y1="-3.15" x2="8.93" y2="-3.15" width="0.1524" layer="21"/>
<wire x1="8.93" y1="3.175" x2="-8.93" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-8.93" y1="3.175" x2="-8.93" y2="-3.15" width="0.1524" layer="21"/>
<wire x1="8.93" y1="-3.15" x2="8.93" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-11.89" y1="0" x2="-10.62" y2="0" width="0.8" layer="51"/>
<wire x1="10.62" y1="0" x2="11.89" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-11.89" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="11.89" y="0" drill="1.1" diameter="2"/>
<text x="-8.8" y="3.525" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-10.62" y1="-0.4" x2="-9.005" y2="0.4" layer="21"/>
<rectangle x1="9.005" y1="-0.4" x2="10.62" y2="0.4" layer="21"/>
</package>
<package name="RWM6X34">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-16.78" y1="-3.625" x2="16.78" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="16.78" y1="3.625" x2="-16.78" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-16.78" y1="3.625" x2="-16.78" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="16.78" y1="-3.625" x2="16.78" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-19.74" y1="0" x2="-18.47" y2="0" width="0.8" layer="51"/>
<wire x1="18.47" y1="0" x2="19.74" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-19.74" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="19.74" y="0" drill="1.1" diameter="2"/>
<text x="-16.565" y="4.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-18.47" y1="-0.4" x2="-16.855" y2="0.4" layer="21"/>
<rectangle x1="16.855" y1="-0.4" x2="18.47" y2="0.4" layer="21"/>
</package>
<package name="RWM8X26">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-12.28" y1="-3.625" x2="12.28" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="12.28" y1="3.625" x2="-12.28" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-12.28" y1="3.625" x2="-12.28" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="12.28" y1="-3.625" x2="12.28" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="0" x2="-13.97" y2="0" width="0.8" layer="51"/>
<wire x1="13.97" y1="0" x2="15.24" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-15.24" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="15.24" y="0" drill="1.1" diameter="2"/>
<text x="-12.065" y="4.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-13.97" y1="-0.4" x2="-12.355" y2="0.4" layer="21"/>
<rectangle x1="12.355" y1="-0.4" x2="13.97" y2="0.4" layer="21"/>
</package>
<package name="RWM8X34">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-16.78" y1="-3.625" x2="16.78" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="16.78" y1="3.625" x2="-16.78" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-16.78" y1="3.625" x2="-16.78" y2="-3.625" width="0.1524" layer="21"/>
<wire x1="16.78" y1="-3.625" x2="16.78" y2="3.625" width="0.1524" layer="21"/>
<wire x1="-19.74" y1="0" x2="-18.47" y2="0" width="0.8" layer="51"/>
<wire x1="18.47" y1="0" x2="19.74" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-19.74" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="19.74" y="0" drill="1.1" diameter="2"/>
<text x="-16.565" y="4.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-18.47" y1="-0.4" x2="-16.855" y2="0.4" layer="21"/>
<rectangle x1="16.855" y1="-0.4" x2="18.47" y2="0.4" layer="21"/>
</package>
<package name="RWM8X45">
<description>&lt;b&gt;Enamelled Wirewound Power Resistors Axial Leads&lt;/b&gt;&lt;p&gt;
Source: www.vishay.com .. rwm.pdf</description>
<wire x1="-22.78" y1="-4.625" x2="22.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="22.78" y1="4.625" x2="-22.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-22.78" y1="4.625" x2="-22.78" y2="-4.625" width="0.1524" layer="21"/>
<wire x1="22.78" y1="-4.625" x2="22.78" y2="4.625" width="0.1524" layer="21"/>
<wire x1="-25.74" y1="0" x2="-24.47" y2="0" width="0.8" layer="51"/>
<wire x1="24.47" y1="0" x2="25.74" y2="0" width="0.8" layer="51"/>
<pad name="1" x="-25.74" y="0" drill="1.1" diameter="2"/>
<pad name="2" x="25.74" y="0" drill="1.1" diameter="2"/>
<text x="-22.565" y="5.125" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-24.47" y1="-0.4" x2="-22.855" y2="0.4" layer="21"/>
<rectangle x1="22.855" y1="-0.4" x2="24.47" y2="0.4" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="R">
<wire x1="-3.81" y1="-0.889" x2="3.81" y2="-0.889" width="0.254" layer="94"/>
<wire x1="3.81" y1="-0.889" x2="3.81" y2="0" width="0.254" layer="94"/>
<wire x1="3.81" y1="0.889" x2="-3.81" y2="0.889" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-0.889" x2="-3.81" y2="0" width="0.254" layer="94"/>
<wire x1="3.81" y1="0" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="3.81" y1="0" x2="3.81" y2="0.889" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-3.81" y2="0" width="0.1524" layer="94"/>
<wire x1="-3.81" y1="0" x2="-3.81" y2="0.889" width="0.254" layer="94"/>
<text x="-3.81" y="1.3716" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-2.921" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" prefix="R" uservalue="yes">
<description>Power Resitor</description>
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="HS10" package="HS10">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="OHMITE" constant="no"/>
<attribute name="MPN" value="RHS10K" constant="no"/>
<attribute name="OC_FARNELL" value="1050333" constant="no"/>
<attribute name="OC_NEWARK" value="01F7568" constant="no"/>
</technology>
</technologies>
</device>
<device name="HS15" package="HS15">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="OHMITE" constant="no"/>
<attribute name="MPN" value="RHS15KE" constant="no"/>
<attribute name="OC_FARNELL" value="1158722" constant="no"/>
<attribute name="OC_NEWARK" value="64K5744" constant="no"/>
</technology>
</technologies>
</device>
<device name="HS25" package="HS25">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="RHS25K" constant="no"/>
<attribute name="OC_FARNELL" value="1129876" constant="no"/>
<attribute name="OC_NEWARK" value="13P6733" constant="no"/>
</technology>
</technologies>
</device>
<device name="HS50" package="HS50">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="RHS50R" constant="no"/>
<attribute name="OC_FARNELL" value="1050163" constant="no"/>
<attribute name="OC_NEWARK" value="13P6749" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH206-8" package="KH206-8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH206-8R" package="KH206-8R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH208-8" package="KH208-8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH208-8R" package="KH208R-8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH214-8" package="KH214-8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH214-8R" package="KH214R-8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH216-8" package="KH216-8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KH218-8" package="KH218-8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KP290" package="KP290">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KP292" package="KP292">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KP294" package="KP294">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KP296" package="KP296">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KP298" package="KP298">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KWP330" package="KWP330">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KWKP332" package="KWP332">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KWP333" package="KWP333">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KWP335" package="KWP335">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KWP336" package="KWP336">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KWP337" package="KWP337">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="KWP338" package="KWP338">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="MNS-2" package="MNS-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="MNS-5" package="MNS-5">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="MPC70-2" package="MPC70-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="MPC71-5" package="MPC71-5">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="AC01" package="AC01">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="AC03" package="AC03">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="AC04" package="AC04">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="AC05" package="AC05">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="AC07" package="AC07">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="AC10" package="AC10">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA0001" package="CA0001">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA0002" package="CA0002">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4050" package="CA4050">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4055" package="CA4055">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4060" package="CA4060">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4070" package="CA4070">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4080" package="CA4080">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4090" package="CA4090">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4100" package="CA4100">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4150" package="CA4150">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4200" package="CA4200">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA4220" package="CA4220">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5050" package="CA5050">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5055" package="CA5055">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5060" package="CA5060">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5070" package="CA5070">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5080" package="CA5080">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5090" package="CA5090">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5100" package="CA5100">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5150" package="CA5150">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5200" package="CA5200">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CA5220" package="CA5220">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HPS523" package="HPS523">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HPS58" package="HPS58">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HPS63" package="HPS63">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HPS68" package="HPS68">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HPS923" package="HPS923">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HPS932" package="HPS932">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HPS947" package="HPS947">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS002" package="RS002">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS007" package="RS007">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS01A" package="RS01A">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS01M" package="RS01M">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS02B" package="RS02B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS02C" package="RS02C">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS02C_17-23" package="RS02C_17-23">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS02M" package="RS02M">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS05_69-70" package="RS05_69-70">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS1/2" package="RS1/2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="OHMITE" constant="no"/>
<attribute name="MPN" value="RRS1K0E" constant="no"/>
<attribute name="OC_FARNELL" value="1762006" constant="no"/>
<attribute name="OC_NEWARK" value="64K5942" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS1/4" package="RS1/4">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="OHMITE" constant="no"/>
<attribute name="MPN" value="RRS1K0" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="01F7661" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS1/8" package="RS1/8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RS10_38-39" package="RS10_38-39">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM10X45" package="RWM10X45">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM10X64" package="RWM10X64">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM10X65" package="RWM10X65">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM4X10" package="RWM4X10">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM4X22" package="RWM4X22">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM5X26" package="RWM5X26">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM6X22" package="RWM6X22">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM6X34" package="RWM6X34">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM8X26" package="RWM8X26">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM8X34" package="RWM8X34">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="RWM8X45" package="RWM8X45">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="smartplug" deviceset="CS5490" device=""/>
<part name="Y1" library="SparkFun" deviceset="CRYSTAL" device="10.5X4.8" value="4.096MHz"/>
<part name="C1" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="C2" library="SparkFun" deviceset="CAP" device="0603-CAP" value="220pF"/>
<part name="C3" library="SparkFun" deviceset="CAP" device="0603-CAP" value="220pF"/>
<part name="GND1" library="supply1" deviceset="GNDA" device=""/>
<part name="C4" library="SparkFun" deviceset="CAP" device="0603-CAP" value="22nF"/>
<part name="R1" library="Rebel" deviceset="R-EU_" device="0603" value="0R"/>
<part name="R2" library="Rebel" deviceset="R-EU_" device="0603" value="1K"/>
<part name="R3" library="Rebel" deviceset="R-EU_" device="0603" value="1K"/>
<part name="R4" library="Rebel" deviceset="R-EU_" device="0603" value="422K"/>
<part name="R5" library="Rebel" deviceset="R-EU_" device="0603" value="422K"/>
<part name="R6" library="Rebel" deviceset="R-EU_" device="0603" value="422K"/>
<part name="GND2" library="supply1" deviceset="GNDA" device=""/>
<part name="VR1" library="varistor" deviceset="S10K250" device=""/>
<part name="C5" library="SparkFun" deviceset="CAP" device="0603-CAP" value="10nF"/>
<part name="GND3" library="supply1" deviceset="GNDA" device=""/>
<part name="C6" library="SparkFun" deviceset="CAP" device="0603-CAP" value="220pF"/>
<part name="C7" library="SparkFun" deviceset="CAP" device="0603-CAP" value="220pF"/>
<part name="GND4" library="supply1" deviceset="GNDA" device=""/>
<part name="C8" library="SparkFun" deviceset="CAP" device="0603-CAP" value="22nF"/>
<part name="R7" library="Rebel" deviceset="R-EU_" device="0603" value="1K"/>
<part name="R8" library="Rebel" deviceset="R-EU_" device="0603" value="1K"/>
<part name="R9" library="SparkFun" deviceset="RESISTOR" device="2512" value="0R002"/>
<part name="GND5" library="supply1" deviceset="GNDA" device=""/>
<part name="R11" library="Rebel" deviceset="R-EU_" device="0603" value="100R"/>
<part name="LED1" library="Rebel" deviceset="LED" device="3MM" value="BLUE"/>
<part name="C9" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="C10" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="GND6" library="supply1" deviceset="GNDA" device=""/>
<part name="DC1" library="smartplug" deviceset="MEU1S0503ZC" device="D"/>
<part name="GND7" library="supply1" deviceset="GNDA" device=""/>
<part name="C11" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="OK1" library="smartplug" deviceset="SFH610A-3" device="TH"/>
<part name="GND8" library="supply1" deviceset="GNDA" device=""/>
<part name="GND9" library="supply1" deviceset="GNDA" device=""/>
<part name="R12" library="Rebel" deviceset="R-EU_" device="0603" value="4K7"/>
<part name="R13" library="Rebel" deviceset="R-EU_" device="0603" value="1K"/>
<part name="C12" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="OK2" library="smartplug" deviceset="SFH610A-3" device="TH"/>
<part name="GND10" library="supply1" deviceset="GNDA" device=""/>
<part name="GND11" library="supply1" deviceset="GNDA" device=""/>
<part name="R14" library="Rebel" deviceset="R-EU_" device="0603" value="4K7"/>
<part name="R15" library="Rebel" deviceset="R-EU_" device="0603" value="1K"/>
<part name="OK3" library="smartplug" deviceset="SFH610A-3" device="TH"/>
<part name="R16" library="Rebel" deviceset="R-EU_" device="0603" value="4K7"/>
<part name="R17" library="Rebel" deviceset="R-EU_" device="0603" value="680R"/>
<part name="TR1" library="smartplug" deviceset="VTX-214-003-105" device="" value="VTX-214-003-105"/>
<part name="L1" library="smartplug" deviceset="RLB0914-4R7ML" device="A" value="5uH"/>
<part name="C13" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="47uF"/>
<part name="SUPPLY1" library="supply2" deviceset="DGND" device=""/>
<part name="K1" library="smartplug" deviceset="S216S01F" device="A"/>
<part name="SUPPLY2" library="supply2" deviceset="DGND" device=""/>
<part name="SUPPLY3" library="supply2" deviceset="DGND" device=""/>
<part name="T1" library="smartplug" deviceset="2N3904" device=""/>
<part name="D1" library="adafruit" deviceset="1N4004" device=""/>
<part name="U$2" library="smartplug" deviceset="PHOTON" device="_WITH_HEADERS"/>
<part name="SUPPLY4" library="supply2" deviceset="DGND" device=""/>
<part name="SUPPLY5" library="supply2" deviceset="DGND" device=""/>
<part name="F1" library="smartplug" deviceset="SH32" device="" value="T15A 1 1/4&quot;"/>
<part name="U1" library="smartplug" deviceset="MCP16301T-I/CHY" device=""/>
<part name="R10" library="Rebel" deviceset="R-EU_" device="0204/7" value="220"/>
<part name="C14" library="smartplug" deviceset="ECQ" device="-L25.5" technology="U2A684KLA" value="0.68UF"/>
<part name="U$3" library="SparkFun" deviceset="DIODE-ZENER" device="PTH"/>
<part name="U$4" library="SparkFun" deviceset="DIODE-ZENER" device="PTH"/>
<part name="GND12" library="supply1" deviceset="GNDA" device=""/>
<part name="C15" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="47uF"/>
<part name="U$5" library="SparkFun" deviceset="DIODE-ZENER" device="PTH"/>
<part name="R18" library="Rebel" deviceset="R-EU_" device="0204/7" value="220"/>
<part name="GND13" library="supply1" deviceset="GNDA" device=""/>
<part name="C16" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="10uF"/>
<part name="D6" library="diode" deviceset="1N581*" device="" technology="7-B"/>
<part name="GND14" library="supply1" deviceset="GNDA" device=""/>
<part name="L2" library="smartplug" deviceset="RLB0914-4R7ML" device="A"/>
<part name="D7" library="Rebel" deviceset="DIODE" device="1N4148"/>
<part name="C17" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="R19" library="Rebel" deviceset="R-EU_" device="0204/7" value="52K3"/>
<part name="R20" library="Rebel" deviceset="R-EU_" device="0204/7" value="10K"/>
<part name="GND15" library="supply1" deviceset="GNDA" device=""/>
<part name="C18" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="10uF"/>
<part name="C19" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="10uF"/>
<part name="GND16" library="supply1" deviceset="GNDA" device=""/>
<part name="D2" library="Rebel" deviceset="DIODE" device="1N4001"/>
<part name="D3" library="Rebel" deviceset="DIODE" device="1N4001"/>
<part name="D4" library="Rebel" deviceset="DIODE" device="1N4001"/>
<part name="D5" library="Rebel" deviceset="DIODE" device="1N4001"/>
<part name="U2" library="smartplug" deviceset="UCC28722" device=""/>
<part name="R21" library="resistor-power" deviceset="R" device="AC03" value="10R 3W"/>
<part name="D8" library="Rebel" deviceset="DIODE" device="1N4001" value="1N4007"/>
<part name="L3" library="smartplug" deviceset="RLB0914-4R7ML" device="A" value="4.7uH"/>
<part name="R22" library="varistor" deviceset="VARISTOR" device="S07K11"/>
<part name="C20" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="C21" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="10uF"/>
<part name="C22" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="10uF"/>
<part name="R23" library="Rebel" deviceset="R-EU_" device="0204/7" value="1M"/>
<part name="R24" library="Rebel" deviceset="R-EU_" device="0204/7" value="1M"/>
<part name="R25" library="Rebel" deviceset="R-EU_" device="0204/7" value="1M"/>
<part name="R26" library="Rebel" deviceset="R-EU_" device="0204/7" value="1M"/>
<part name="GND17" library="supply1" deviceset="GNDA" device=""/>
<part name="Q1" library="smartplug" deviceset="KSC5026M" device=""/>
<part name="D9" library="Rebel" deviceset="DIODE" device="1N4001" value="FR107"/>
<part name="C23" library="SparkFun" deviceset="CAP_POL" device="PTH1" value="10uF"/>
<part name="R27" library="Rebel" deviceset="R-EU_" device="0204/7" value="0R75"/>
<part name="R28" library="Rebel" deviceset="R-EU_" device="0204/7" value="365K"/>
<part name="R29" library="Rebel" deviceset="R-EU_" device="0204/7" value="150K"/>
<part name="L4" library="smartplug" deviceset="RLB0914-4R7ML" device="A" value="820uH"/>
<part name="D10" library="Rebel" deviceset="DIODE" device="1N4001" value="FR107"/>
<part name="GND18" library="supply1" deviceset="GNDA" device=""/>
<part name="C25" library="SparkFun" deviceset="CAP" device="0603-CAP" value="100nF"/>
<part name="R30" library="Rebel" deviceset="R-EU_" device="0204/7" value="68.1K"/>
<part name="C26" library="smartplug" deviceset="CAP_POL" device="PTH1" value="220uF"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="-5.08" y="-114.3" size="6.4516" layer="150">ALT PSU</text>
<text x="-25.4" y="-193.04" size="6.4516" layer="150">ALT2 PSU</text>
<text x="-134.62" y="121.92" size="6.4516" layer="150">Biscuit Smartplug Prototype Design</text>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="86.36" y="48.26"/>
<instance part="Y1" gate="G$1" x="109.22" y="48.26" rot="R180"/>
<instance part="C1" gate="G$1" x="96.52" y="40.64" smashed="yes" rot="R90">
<attribute name="NAME" x="92.456" y="42.799" size="1.778" layer="95"/>
<attribute name="VALUE" x="103.759" y="39.624" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="C2" gate="G$1" x="27.94" y="33.02"/>
<instance part="C3" gate="G$1" x="27.94" y="43.18"/>
<instance part="GND1" gate="1" x="43.18" y="38.1"/>
<instance part="C4" gate="G$1" x="15.24" y="38.1"/>
<instance part="R1" gate="G$1" x="7.62" y="48.26"/>
<instance part="R2" gate="G$1" x="7.62" y="27.94"/>
<instance part="R3" gate="G$1" x="0" y="38.1" rot="R90"/>
<instance part="R4" gate="G$1" x="-5.08" y="48.26"/>
<instance part="R5" gate="G$1" x="-15.24" y="48.26"/>
<instance part="R6" gate="G$1" x="-25.4" y="48.26"/>
<instance part="GND2" gate="1" x="0" y="25.4"/>
<instance part="VR1" gate="1" x="-35.56" y="33.02" rot="R90"/>
<instance part="C5" gate="G$1" x="-45.72" y="35.56"/>
<instance part="GND3" gate="1" x="-40.64" y="22.86"/>
<instance part="C6" gate="G$1" x="27.94" y="60.96"/>
<instance part="C7" gate="G$1" x="27.94" y="73.66"/>
<instance part="GND4" gate="1" x="43.18" y="63.5"/>
<instance part="C8" gate="G$1" x="15.24" y="63.5"/>
<instance part="R7" gate="G$1" x="7.62" y="78.74"/>
<instance part="R8" gate="G$1" x="2.54" y="55.88"/>
<instance part="R9" gate="G$1" x="-2.54" y="66.04" rot="R90"/>
<instance part="GND5" gate="1" x="76.2" y="25.4"/>
<instance part="R11" gate="G$1" x="93.98" y="86.36" rot="R90"/>
<instance part="LED1" gate="G$1" x="93.98" y="99.06"/>
<instance part="C9" gate="G$1" x="60.96" y="86.36" smashed="yes" rot="R90">
<attribute name="NAME" x="56.896" y="88.519" size="1.778" layer="95"/>
<attribute name="VALUE" x="68.199" y="85.344" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="C10" gate="G$1" x="60.96" y="93.98" smashed="yes" rot="R90">
<attribute name="NAME" x="56.896" y="96.139" size="1.778" layer="95"/>
<attribute name="VALUE" x="68.199" y="92.964" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND6" gate="1" x="48.26" y="83.82"/>
<instance part="DC1" gate="G$1" x="-22.86" y="-53.34"/>
<instance part="GND7" gate="1" x="-7.62" y="-71.12" smashed="yes">
<attribute name="VALUE" x="-10.16" y="-73.66" size="1.778" layer="96"/>
</instance>
<instance part="C11" gate="G$1" x="175.26" y="53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="173.101" y="49.276" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="176.276" y="60.579" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="OK1" gate="G$1" x="200.66" y="53.34" rot="MR0"/>
<instance part="GND8" gate="1" x="185.42" y="43.18" smashed="yes">
<attribute name="VALUE" x="182.88" y="40.64" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="GND9" gate="1" x="175.26" y="43.18" smashed="yes">
<attribute name="VALUE" x="172.72" y="40.64" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R12" gate="G$1" x="182.88" y="68.58" rot="R90"/>
<instance part="R13" gate="G$1" x="223.52" y="50.8" rot="R180"/>
<instance part="C12" gate="G$1" x="177.8" y="-66.04" smashed="yes" rot="R180">
<attribute name="NAME" x="175.641" y="-70.104" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="178.816" y="-58.801" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="OK2" gate="G$1" x="203.2" y="-66.04" rot="MR0"/>
<instance part="GND10" gate="1" x="187.96" y="-76.2" smashed="yes">
<attribute name="VALUE" x="185.42" y="-78.74" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="GND11" gate="1" x="177.8" y="-76.2" smashed="yes">
<attribute name="VALUE" x="175.26" y="-78.74" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R14" gate="G$1" x="185.42" y="-50.8" rot="R90"/>
<instance part="R15" gate="G$1" x="226.06" y="-68.58" rot="R180"/>
<instance part="OK3" gate="G$1" x="200.66" y="-5.08"/>
<instance part="R16" gate="G$1" x="220.98" y="7.62" rot="R90"/>
<instance part="R17" gate="G$1" x="180.34" y="-7.62" rot="R180"/>
<instance part="TR1" gate="1" x="-99.06" y="-53.34"/>
<instance part="L1" gate="G$1" x="-81.28" y="-50.8" rot="R90"/>
<instance part="C13" gate="G$1" x="-71.12" y="-55.88"/>
<instance part="SUPPLY1" gate="G$1" x="-83.82" y="-66.04"/>
<instance part="K1" gate="G$1" x="-119.38" y="63.5"/>
<instance part="SUPPLY2" gate="G$1" x="220.98" y="-15.24"/>
<instance part="SUPPLY3" gate="G$1" x="-134.62" y="35.56"/>
<instance part="T1" gate="G1" x="-137.16" y="45.72"/>
<instance part="D1" gate="1" x="-134.62" y="63.5" rot="R90"/>
<instance part="U$2" gate="G$1" x="76.2" y="-60.96"/>
<instance part="SUPPLY4" gate="G$1" x="43.18" y="-35.56"/>
<instance part="SUPPLY5" gate="G$1" x="106.68" y="-53.34"/>
<instance part="F1" gate="G$1" x="-27.94" y="78.74"/>
<instance part="U1" gate="A" x="43.18" y="-144.78"/>
<instance part="R10" gate="G$1" x="-60.96" y="-124.46"/>
<instance part="C14" gate="A" x="-53.34" y="-124.46"/>
<instance part="U$3" gate="G$1" x="-43.18" y="-129.54" rot="R270"/>
<instance part="U$4" gate="G$1" x="-43.18" y="-144.78" rot="R90"/>
<instance part="GND12" gate="1" x="-35.56" y="-139.7"/>
<instance part="C15" gate="G$1" x="-10.16" y="-147.32"/>
<instance part="U$5" gate="G$1" x="0" y="-147.32" rot="R90"/>
<instance part="R18" gate="G$1" x="0" y="-134.62" rot="R90"/>
<instance part="GND13" gate="1" x="-5.08" y="-157.48"/>
<instance part="C16" gate="G$1" x="7.62" y="-147.32"/>
<instance part="D6" gate="G$1" x="66.04" y="-142.24" rot="R90"/>
<instance part="GND14" gate="1" x="66.04" y="-149.86"/>
<instance part="L2" gate="G$1" x="78.74" y="-137.16" rot="R90"/>
<instance part="D7" gate="G$1" x="76.2" y="-121.92" rot="R180"/>
<instance part="C17" gate="G$1" x="68.58" y="-129.54" smashed="yes" rot="R180">
<attribute name="NAME" x="66.421" y="-133.604" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="69.596" y="-122.301" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="R19" gate="G$1" x="86.36" y="-144.78" rot="R90"/>
<instance part="R20" gate="G$1" x="86.36" y="-160.02" rot="R90"/>
<instance part="GND15" gate="1" x="86.36" y="-170.18"/>
<instance part="C18" gate="G$1" x="99.06" y="-142.24"/>
<instance part="C19" gate="G$1" x="106.68" y="-142.24"/>
<instance part="GND16" gate="1" x="101.6" y="-154.94"/>
<instance part="D2" gate="G$1" x="-17.78" y="-129.54"/>
<instance part="D3" gate="G$1" x="-17.78" y="-142.24"/>
<instance part="D4" gate="G$1" x="-30.48" y="-129.54"/>
<instance part="D5" gate="G$1" x="-30.48" y="-142.24"/>
<instance part="U2" gate="A" x="-10.16" y="-223.52"/>
<instance part="R21" gate="G$1" x="-111.76" y="-200.66"/>
<instance part="D8" gate="G$1" x="-96.52" y="-200.66"/>
<instance part="L3" gate="G$1" x="-78.74" y="-200.66" rot="R90"/>
<instance part="R22" gate="G$1" x="-101.6" y="-223.52" rot="R90"/>
<instance part="C20" gate="G$1" x="-88.9" y="-223.52" smashed="yes" rot="R180">
<attribute name="NAME" x="-91.059" y="-227.584" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="-87.884" y="-216.281" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="C21" gate="G$1" x="-68.58" y="-213.36"/>
<instance part="C22" gate="G$1" x="-68.58" y="-233.68"/>
<instance part="R23" gate="G$1" x="-53.34" y="-208.28" rot="R90"/>
<instance part="R24" gate="G$1" x="-53.34" y="-220.98" rot="R90"/>
<instance part="R25" gate="G$1" x="-45.72" y="-226.06" rot="R180"/>
<instance part="R26" gate="G$1" x="-33.02" y="-226.06" rot="R180"/>
<instance part="GND17" gate="1" x="-68.58" y="-251.46"/>
<instance part="Q1" gate="G$1" x="-27.94" y="-203.2" rot="R90"/>
<instance part="D9" gate="G$1" x="-30.48" y="-251.46"/>
<instance part="C23" gate="G$1" x="-12.7" y="-251.46" rot="R90"/>
<instance part="R27" gate="G$1" x="12.7" y="-200.66" rot="R180"/>
<instance part="R28" gate="G$1" x="10.16" y="-261.62" rot="R180"/>
<instance part="R29" gate="G$1" x="-25.4" y="-261.62" rot="R180"/>
<instance part="L4" gate="G$1" x="33.02" y="-200.66" rot="R90"/>
<instance part="D10" gate="G$1" x="25.4" y="-228.6" rot="R90"/>
<instance part="GND18" gate="1" x="25.4" y="-266.7"/>
<instance part="C25" gate="G$1" x="71.12" y="-226.06" smashed="yes" rot="R180">
<attribute name="NAME" x="68.961" y="-230.124" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="72.136" y="-218.821" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="R30" gate="G$1" x="55.88" y="-226.06" rot="R270"/>
<instance part="C26" gate="G$1" x="40.64" y="-226.06"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="XIN"/>
<pinref part="Y1" gate="G$1" pin="2"/>
<wire x1="91.44" y1="48.26" x2="106.68" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="Y1" gate="G$1" pin="1"/>
<wire x1="111.76" y1="48.26" x2="114.3" y2="48.26" width="0.1524" layer="91"/>
<wire x1="114.3" y1="48.26" x2="114.3" y2="43.18" width="0.1524" layer="91"/>
<wire x1="114.3" y1="43.18" x2="101.6" y2="43.18" width="0.1524" layer="91"/>
<wire x1="101.6" y1="43.18" x2="101.6" y2="45.72" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="XOUT"/>
<wire x1="101.6" y1="45.72" x2="91.44" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VREF-"/>
<pinref part="C1" gate="G$1" pin="1"/>
</segment>
</net>
<net name="RX" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="RX"/>
<wire x1="91.44" y1="53.34" x2="99.06" y2="53.34" width="0.1524" layer="91"/>
<label x="99.06" y="55.88" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="C11" gate="G$1" pin="2"/>
<pinref part="OK1" gate="G$1" pin="C"/>
<wire x1="175.26" y1="55.88" x2="182.88" y2="55.88" width="0.1524" layer="91"/>
<wire x1="182.88" y1="55.88" x2="187.96" y2="55.88" width="0.1524" layer="91"/>
<wire x1="175.26" y1="55.88" x2="162.56" y2="55.88" width="0.1524" layer="91"/>
<label x="162.56" y="55.88" size="1.778" layer="95"/>
<pinref part="R12" gate="G$1" pin="1"/>
<wire x1="182.88" y1="63.5" x2="182.88" y2="55.88" width="0.1524" layer="91"/>
<junction x="182.88" y="55.88"/>
<junction x="175.26" y="55.88"/>
</segment>
</net>
<net name="TX" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="TX"/>
<wire x1="91.44" y1="50.8" x2="99.06" y2="50.8" width="0.1524" layer="91"/>
<label x="96.52" y="50.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R17" gate="G$1" pin="2"/>
<wire x1="175.26" y1="-7.62" x2="167.64" y2="-7.62" width="0.1524" layer="91"/>
<label x="165.1" y="-7.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="GNDA" class="0">
<segment>
<pinref part="C2" gate="G$1" pin="1"/>
<pinref part="C3" gate="G$1" pin="2"/>
<pinref part="GND1" gate="1" pin="GNDA"/>
<wire x1="43.18" y1="40.64" x2="27.94" y2="40.64" width="0.1524" layer="91"/>
<wire x1="27.94" y1="40.64" x2="27.94" y2="38.1" width="0.1524" layer="91"/>
<junction x="27.94" y="40.64"/>
</segment>
<segment>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="2.54" y1="27.94" x2="0" y2="27.94" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="1"/>
<wire x1="0" y1="27.94" x2="0" y2="33.02" width="0.1524" layer="91"/>
<pinref part="GND2" gate="1" pin="GNDA"/>
<junction x="0" y="27.94"/>
</segment>
<segment>
<pinref part="C5" gate="G$1" pin="2"/>
<wire x1="-45.72" y1="33.02" x2="-45.72" y2="27.94" width="0.1524" layer="91"/>
<pinref part="VR1" gate="1" pin="1"/>
<wire x1="-45.72" y1="27.94" x2="-40.64" y2="27.94" width="0.1524" layer="91"/>
<pinref part="GND3" gate="1" pin="GNDA"/>
<wire x1="-40.64" y1="27.94" x2="-35.56" y2="27.94" width="0.1524" layer="91"/>
<wire x1="-40.64" y1="25.4" x2="-40.64" y2="27.94" width="0.1524" layer="91"/>
<junction x="-40.64" y="27.94"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GNDA"/>
<pinref part="GND5" gate="1" pin="GNDA"/>
<wire x1="76.2" y1="27.94" x2="76.2" y2="30.48" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C10" gate="G$1" pin="1"/>
<wire x1="55.88" y1="93.98" x2="48.26" y2="93.98" width="0.1524" layer="91"/>
<pinref part="GND6" gate="1" pin="GNDA"/>
<wire x1="48.26" y1="93.98" x2="48.26" y2="86.36" width="0.1524" layer="91"/>
<pinref part="C9" gate="G$1" pin="1"/>
<wire x1="55.88" y1="86.36" x2="48.26" y2="86.36" width="0.1524" layer="91"/>
<junction x="48.26" y="86.36"/>
</segment>
<segment>
<pinref part="C6" gate="G$1" pin="1"/>
<pinref part="C7" gate="G$1" pin="2"/>
<pinref part="GND4" gate="1" pin="GNDA"/>
<wire x1="27.94" y1="66.04" x2="27.94" y2="71.12" width="0.1524" layer="91"/>
<wire x1="43.18" y1="66.04" x2="27.94" y2="66.04" width="0.1524" layer="91"/>
<junction x="27.94" y="66.04"/>
</segment>
<segment>
<pinref part="DC1" gate="G$1" pin="-VOUT"/>
<wire x1="-10.16" y1="-55.88" x2="-7.62" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="-55.88" x2="-7.62" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="GND7" gate="1" pin="GNDA"/>
</segment>
<segment>
<pinref part="OK1" gate="G$1" pin="E"/>
<wire x1="187.96" y1="50.8" x2="185.42" y2="50.8" width="0.1524" layer="91"/>
<pinref part="GND8" gate="1" pin="GNDA"/>
<wire x1="185.42" y1="50.8" x2="185.42" y2="45.72" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND9" gate="1" pin="GNDA"/>
<pinref part="C11" gate="G$1" pin="1"/>
<wire x1="175.26" y1="45.72" x2="175.26" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="OK2" gate="G$1" pin="E"/>
<wire x1="190.5" y1="-68.58" x2="187.96" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="GND10" gate="1" pin="GNDA"/>
<wire x1="187.96" y1="-68.58" x2="187.96" y2="-73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND11" gate="1" pin="GNDA"/>
<pinref part="C12" gate="G$1" pin="1"/>
<wire x1="177.8" y1="-73.66" x2="177.8" y2="-71.12" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND12" gate="1" pin="GNDA"/>
<wire x1="-35.56" y1="-137.16" x2="-35.56" y2="-134.62" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="-129.54" x2="-33.02" y2="-134.62" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="-134.62" x2="-33.02" y2="-142.24" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="-134.62" x2="-33.02" y2="-134.62" width="0.1524" layer="91"/>
<junction x="-33.02" y="-134.62"/>
<pinref part="D4" gate="G$1" pin="A"/>
<pinref part="D5" gate="G$1" pin="A"/>
</segment>
<segment>
<pinref part="C15" gate="G$1" pin="-"/>
<wire x1="-10.16" y1="-152.4" x2="-5.08" y2="-152.4" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="A"/>
<wire x1="-5.08" y1="-152.4" x2="0" y2="-152.4" width="0.1524" layer="91"/>
<wire x1="0" y1="-152.4" x2="0" y2="-149.86" width="0.1524" layer="91"/>
<pinref part="GND13" gate="1" pin="GNDA"/>
<wire x1="-5.08" y1="-154.94" x2="-5.08" y2="-152.4" width="0.1524" layer="91"/>
<junction x="-5.08" y="-152.4"/>
<wire x1="0" y1="-152.4" x2="0" y2="-154.94" width="0.1524" layer="91"/>
<junction x="0" y="-152.4"/>
<pinref part="U1" gate="A" pin="GND"/>
<wire x1="0" y1="-154.94" x2="7.62" y2="-154.94" width="0.1524" layer="91"/>
<pinref part="C16" gate="G$1" pin="-"/>
<wire x1="7.62" y1="-154.94" x2="27.94" y2="-154.94" width="0.1524" layer="91"/>
<wire x1="7.62" y1="-152.4" x2="7.62" y2="-154.94" width="0.1524" layer="91"/>
<junction x="7.62" y="-154.94"/>
</segment>
<segment>
<pinref part="GND14" gate="1" pin="GNDA"/>
<pinref part="D6" gate="G$1" pin="A"/>
<wire x1="66.04" y1="-147.32" x2="66.04" y2="-144.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND15" gate="1" pin="GNDA"/>
<pinref part="R20" gate="G$1" pin="1"/>
<wire x1="86.36" y1="-167.64" x2="86.36" y2="-165.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C18" gate="G$1" pin="-"/>
<pinref part="C19" gate="G$1" pin="-"/>
<wire x1="99.06" y1="-147.32" x2="101.6" y2="-147.32" width="0.1524" layer="91"/>
<pinref part="GND16" gate="1" pin="GNDA"/>
<wire x1="101.6" y1="-147.32" x2="106.68" y2="-147.32" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-152.4" x2="101.6" y2="-147.32" width="0.1524" layer="91"/>
<junction x="101.6" y="-147.32"/>
</segment>
<segment>
<pinref part="R22" gate="G$1" pin="2"/>
<wire x1="-101.6" y1="-228.6" x2="-101.6" y2="-246.38" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="-246.38" x2="-124.46" y2="-246.38" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="-246.38" x2="-124.46" y2="-226.06" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="-226.06" x2="-129.54" y2="-226.06" width="0.1524" layer="91"/>
<label x="-137.16" y="-226.06" size="1.778" layer="95"/>
<wire x1="-101.6" y1="-246.38" x2="-88.9" y2="-246.38" width="0.1524" layer="91"/>
<junction x="-101.6" y="-246.38"/>
<pinref part="C20" gate="G$1" pin="1"/>
<wire x1="-88.9" y1="-246.38" x2="-88.9" y2="-228.6" width="0.1524" layer="91"/>
<wire x1="-88.9" y1="-246.38" x2="-68.58" y2="-246.38" width="0.1524" layer="91"/>
<junction x="-88.9" y="-246.38"/>
<pinref part="C22" gate="G$1" pin="-"/>
<wire x1="-68.58" y1="-246.38" x2="-68.58" y2="-238.76" width="0.1524" layer="91"/>
<pinref part="GND17" gate="1" pin="GNDA"/>
<wire x1="-68.58" y1="-248.92" x2="-68.58" y2="-246.38" width="0.1524" layer="91"/>
<junction x="-68.58" y="-246.38"/>
</segment>
<segment>
<pinref part="D10" gate="G$1" pin="A"/>
<pinref part="GND18" gate="1" pin="GNDA"/>
<wire x1="25.4" y1="-231.14" x2="25.4" y2="-261.62" width="0.1524" layer="91"/>
<wire x1="25.4" y1="-261.62" x2="25.4" y2="-264.16" width="0.1524" layer="91"/>
<wire x1="40.64" y1="-231.14" x2="40.64" y2="-261.62" width="0.1524" layer="91"/>
<wire x1="40.64" y1="-261.62" x2="25.4" y2="-261.62" width="0.1524" layer="91"/>
<junction x="25.4" y="-261.62"/>
<pinref part="R30" gate="G$1" pin="2"/>
<wire x1="55.88" y1="-231.14" x2="55.88" y2="-261.62" width="0.1524" layer="91"/>
<wire x1="55.88" y1="-261.62" x2="40.64" y2="-261.62" width="0.1524" layer="91"/>
<junction x="40.64" y="-261.62"/>
<pinref part="C25" gate="G$1" pin="1"/>
<wire x1="71.12" y1="-231.14" x2="71.12" y2="-261.62" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-261.62" x2="55.88" y2="-261.62" width="0.1524" layer="91"/>
<junction x="55.88" y="-261.62"/>
<wire x1="71.12" y1="-261.62" x2="119.38" y2="-261.62" width="0.1524" layer="91"/>
<junction x="71.12" y="-261.62"/>
<pinref part="C26" gate="G$1" pin="-"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="C4" gate="G$1" pin="2"/>
<wire x1="15.24" y1="35.56" x2="15.24" y2="27.94" width="0.1524" layer="91"/>
<pinref part="R2" gate="G$1" pin="2"/>
<wire x1="15.24" y1="27.94" x2="12.7" y2="27.94" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="VIN-"/>
<wire x1="50.8" y1="40.64" x2="50.8" y2="27.94" width="0.1524" layer="91"/>
<wire x1="15.24" y1="27.94" x2="27.94" y2="27.94" width="0.1524" layer="91"/>
<pinref part="C2" gate="G$1" pin="2"/>
<wire x1="50.8" y1="27.94" x2="27.94" y2="27.94" width="0.1524" layer="91"/>
<wire x1="27.94" y1="27.94" x2="27.94" y2="30.48" width="0.1524" layer="91"/>
<junction x="27.94" y="27.94"/>
<junction x="15.24" y="27.94"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="C3" gate="G$1" pin="1"/>
<pinref part="C4" gate="G$1" pin="1"/>
<wire x1="15.24" y1="43.18" x2="15.24" y2="48.26" width="0.1524" layer="91"/>
<wire x1="15.24" y1="48.26" x2="27.94" y2="48.26" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="2"/>
<wire x1="12.7" y1="48.26" x2="15.24" y2="48.26" width="0.1524" layer="91"/>
<junction x="15.24" y="48.26"/>
<wire x1="27.94" y1="48.26" x2="48.26" y2="48.26" width="0.1524" layer="91"/>
<wire x1="48.26" y1="48.26" x2="48.26" y2="45.72" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="VIN+"/>
<wire x1="48.26" y1="45.72" x2="50.8" y2="45.72" width="0.1524" layer="91"/>
<junction x="27.94" y="48.26"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="R3" gate="G$1" pin="2"/>
<wire x1="0" y1="43.18" x2="0" y2="48.26" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="0" y1="48.26" x2="2.54" y2="48.26" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="2"/>
<junction x="0" y="48.26"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="R4" gate="G$1" pin="1"/>
<pinref part="R5" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="R5" gate="G$1" pin="1"/>
<pinref part="R6" gate="G$1" pin="2"/>
</segment>
</net>
<net name="NEUTRAL" class="0">
<segment>
<pinref part="VR1" gate="1" pin="2"/>
<wire x1="-35.56" y1="38.1" x2="-35.56" y2="48.26" width="0.1524" layer="91"/>
<pinref part="R6" gate="G$1" pin="1"/>
<wire x1="-35.56" y1="48.26" x2="-30.48" y2="48.26" width="0.1524" layer="91"/>
<pinref part="C5" gate="G$1" pin="1"/>
<wire x1="-45.72" y1="40.64" x2="-45.72" y2="48.26" width="0.1524" layer="91"/>
<wire x1="-45.72" y1="48.26" x2="-35.56" y2="48.26" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="58.42" x2="-35.56" y2="48.26" width="0.1524" layer="91"/>
<label x="-35.56" y="58.42" size="1.778" layer="95"/>
<junction x="-35.56" y="48.26"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="A"/>
<wire x1="-43.18" y1="-147.32" x2="-43.18" y2="-149.86" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="-149.86" x2="-71.12" y2="-149.86" width="0.1524" layer="91"/>
<wire x1="-27.94" y1="-142.24" x2="-25.4" y2="-142.24" width="0.1524" layer="91"/>
<wire x1="-25.4" y1="-142.24" x2="-20.32" y2="-142.24" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="-149.86" x2="-25.4" y2="-149.86" width="0.1524" layer="91"/>
<wire x1="-25.4" y1="-149.86" x2="-25.4" y2="-142.24" width="0.1524" layer="91"/>
<junction x="-43.18" y="-149.86"/>
<junction x="-25.4" y="-142.24"/>
<pinref part="D3" gate="G$1" pin="A"/>
<pinref part="D5" gate="G$1" pin="C"/>
<label x="-73.66" y="-149.86" size="1.778" layer="95"/>
</segment>
</net>
<net name="LINE_OUT" class="0">
<segment>
<pinref part="R9" gate="G$1" pin="1"/>
<pinref part="R8" gate="G$1" pin="1"/>
<wire x1="-2.54" y1="60.96" x2="-2.54" y2="55.88" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="55.88" x2="-15.24" y2="55.88" width="0.1524" layer="91"/>
<wire x1="-15.24" y1="55.88" x2="-15.24" y2="60.96" width="0.1524" layer="91"/>
<label x="-20.32" y="60.96" size="1.778" layer="95"/>
<junction x="-2.54" y="55.88"/>
</segment>
<segment>
<pinref part="K1" gate="G$1" pin="DS1"/>
<wire x1="-109.22" y1="66.04" x2="-101.6" y2="66.04" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="66.04" x2="-101.6" y2="78.74" width="0.1524" layer="91"/>
<label x="-104.14" y="78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="LIVE" class="0">
<segment>
<pinref part="R9" gate="G$1" pin="2"/>
<wire x1="-2.54" y1="71.12" x2="-2.54" y2="78.74" width="0.1524" layer="91"/>
<pinref part="R7" gate="G$1" pin="1"/>
<wire x1="-2.54" y1="78.74" x2="2.54" y2="78.74" width="0.1524" layer="91"/>
<pinref part="F1" gate="G$1" pin="2A"/>
<wire x1="-22.86" y1="78.74" x2="-2.54" y2="78.74" width="0.1524" layer="91"/>
<junction x="-2.54" y="78.74"/>
</segment>
<segment>
<pinref part="F1" gate="G$1" pin="1A"/>
<wire x1="-33.02" y1="78.74" x2="-40.64" y2="78.74" width="0.1524" layer="91"/>
<label x="-43.18" y="78.74" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R10" gate="G$1" pin="1"/>
<wire x1="-66.04" y1="-124.46" x2="-71.12" y2="-124.46" width="0.1524" layer="91"/>
<label x="-73.66" y="-124.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R21" gate="G$1" pin="1"/>
<wire x1="-116.84" y1="-200.66" x2="-124.46" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="-200.66" x2="-124.46" y2="-220.98" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="-220.98" x2="-129.54" y2="-220.98" width="0.1524" layer="91"/>
<label x="-132.08" y="-220.98" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VREF+"/>
<wire x1="91.44" y1="43.18" x2="99.06" y2="43.18" width="0.1524" layer="91"/>
<pinref part="C1" gate="G$1" pin="2"/>
<wire x1="99.06" y1="43.18" x2="99.06" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="R11" gate="G$1" pin="2"/>
<pinref part="LED1" gate="G$1" pin="C"/>
<wire x1="93.98" y1="91.44" x2="93.98" y2="93.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VDDD"/>
<pinref part="C9" gate="G$1" pin="2"/>
<wire x1="63.5" y1="68.58" x2="63.5" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VDDA"/>
<wire x1="71.12" y1="68.58" x2="71.12" y2="78.74" width="0.1524" layer="91"/>
<pinref part="C10" gate="G$1" pin="2"/>
<wire x1="71.12" y1="78.74" x2="71.12" y2="93.98" width="0.1524" layer="91"/>
<wire x1="71.12" y1="93.98" x2="63.5" y2="93.98" width="0.1524" layer="91"/>
<wire x1="71.12" y1="93.98" x2="71.12" y2="101.6" width="0.1524" layer="91"/>
<label x="71.12" y="101.6" size="1.778" layer="95"/>
<junction x="71.12" y="93.98"/>
<pinref part="U$1" gate="G$1" pin="MODE"/>
<wire x1="78.74" y1="68.58" x2="78.74" y2="78.74" width="0.1524" layer="91"/>
<wire x1="78.74" y1="78.74" x2="71.12" y2="78.74" width="0.1524" layer="91"/>
<junction x="71.12" y="78.74"/>
</segment>
<segment>
<pinref part="LED1" gate="G$1" pin="A"/>
<wire x1="93.98" y1="101.6" x2="93.98" y2="106.68" width="0.1524" layer="91"/>
<label x="93.98" y="106.68" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DC1" gate="G$1" pin="+VOUT"/>
<wire x1="-10.16" y1="-50.8" x2="-7.62" y2="-50.8" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="-50.8" x2="-7.62" y2="-38.1" width="0.1524" layer="91"/>
<label x="-7.62" y="-38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R12" gate="G$1" pin="2"/>
<wire x1="182.88" y1="73.66" x2="182.88" y2="83.82" width="0.1524" layer="91"/>
<label x="182.88" y="83.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R14" gate="G$1" pin="2"/>
<wire x1="185.42" y1="-45.72" x2="185.42" y2="-35.56" width="0.1524" layer="91"/>
<label x="185.42" y="-35.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="OK3" gate="G$1" pin="AC1"/>
<wire x1="190.5" y1="-2.54" x2="187.96" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="187.96" y1="-2.54" x2="187.96" y2="15.24" width="0.1524" layer="91"/>
<label x="187.96" y="15.24" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="3V3"/>
<wire x1="93.98" y1="-33.02" x2="99.06" y2="-33.02" width="0.1524" layer="91"/>
<wire x1="99.06" y1="-33.02" x2="99.06" y2="-25.4" width="0.1524" layer="91"/>
<label x="99.06" y="-22.86" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="R11" gate="G$1" pin="1"/>
<wire x1="93.98" y1="81.28" x2="93.98" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="D0"/>
<wire x1="93.98" y1="60.96" x2="91.44" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="!RESET" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="!RESET"/>
<wire x1="91.44" y1="38.1" x2="96.52" y2="38.1" width="0.1524" layer="91"/>
<wire x1="96.52" y1="38.1" x2="96.52" y2="22.86" width="0.1524" layer="91"/>
<label x="96.52" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="C12" gate="G$1" pin="2"/>
<wire x1="177.8" y1="-63.5" x2="185.42" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="177.8" y1="-63.5" x2="165.1" y2="-63.5" width="0.1524" layer="91"/>
<label x="165.1" y="-63.5" size="1.778" layer="95"/>
<pinref part="R14" gate="G$1" pin="1"/>
<wire x1="185.42" y1="-55.88" x2="185.42" y2="-63.5" width="0.1524" layer="91"/>
<pinref part="OK2" gate="G$1" pin="C"/>
<wire x1="185.42" y1="-63.5" x2="190.5" y2="-63.5" width="0.1524" layer="91"/>
<junction x="185.42" y="-63.5"/>
<junction x="177.8" y="-63.5"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="C8" gate="G$1" pin="2"/>
<wire x1="15.24" y1="60.96" x2="15.24" y2="55.88" width="0.1524" layer="91"/>
<pinref part="R8" gate="G$1" pin="2"/>
<wire x1="7.62" y1="55.88" x2="15.24" y2="55.88" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="IIN+"/>
<wire x1="15.24" y1="55.88" x2="27.94" y2="55.88" width="0.1524" layer="91"/>
<wire x1="50.8" y1="55.88" x2="27.94" y2="55.88" width="0.1524" layer="91"/>
<pinref part="C6" gate="G$1" pin="2"/>
<wire x1="27.94" y1="55.88" x2="27.94" y2="58.42" width="0.1524" layer="91"/>
<junction x="15.24" y="55.88"/>
<junction x="27.94" y="55.88"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="C8" gate="G$1" pin="1"/>
<pinref part="U$1" gate="G$1" pin="IIN-"/>
<wire x1="50.8" y1="60.96" x2="50.8" y2="78.74" width="0.1524" layer="91"/>
<pinref part="C7" gate="G$1" pin="1"/>
<wire x1="27.94" y1="78.74" x2="50.8" y2="78.74" width="0.1524" layer="91"/>
<pinref part="R7" gate="G$1" pin="2"/>
<wire x1="27.94" y1="78.74" x2="15.24" y2="78.74" width="0.1524" layer="91"/>
<wire x1="15.24" y1="78.74" x2="12.7" y2="78.74" width="0.1524" layer="91"/>
<wire x1="15.24" y1="68.58" x2="15.24" y2="78.74" width="0.1524" layer="91"/>
<junction x="15.24" y="78.74"/>
<junction x="27.94" y="78.74"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="OK1" gate="G$1" pin="AC1"/>
<wire x1="210.82" y1="55.88" x2="220.98" y2="55.88" width="0.1524" layer="91"/>
<wire x1="220.98" y1="55.88" x2="220.98" y2="73.66" width="0.1524" layer="91"/>
<label x="220.98" y="73.66" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="OK2" gate="G$1" pin="AC1"/>
<wire x1="213.36" y1="-63.5" x2="223.52" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="223.52" y1="-63.5" x2="223.52" y2="-45.72" width="0.1524" layer="91"/>
<label x="223.52" y="-45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R16" gate="G$1" pin="2"/>
<wire x1="220.98" y1="12.7" x2="220.98" y2="22.86" width="0.1524" layer="91"/>
<label x="218.44" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="C13" gate="G$1" pin="+"/>
<wire x1="-71.12" y1="-53.34" x2="-71.12" y2="-50.8" width="0.1524" layer="91"/>
<pinref part="L1" gate="G$1" pin="2"/>
<wire x1="-71.12" y1="-50.8" x2="-76.2" y2="-50.8" width="0.1524" layer="91"/>
<pinref part="DC1" gate="G$1" pin="+VIN"/>
<wire x1="-71.12" y1="-50.8" x2="-58.42" y2="-50.8" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="-50.8" x2="-35.56" y2="-50.8" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="-50.8" x2="-58.42" y2="-30.48" width="0.1524" layer="91"/>
<label x="-58.42" y="-30.48" size="1.778" layer="95"/>
<junction x="-71.12" y="-50.8"/>
<junction x="-58.42" y="-50.8"/>
</segment>
<segment>
<pinref part="K1" gate="G$1" pin="A"/>
<wire x1="-129.54" y1="66.04" x2="-129.54" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-129.54" y1="68.58" x2="-129.54" y2="78.74" width="0.1524" layer="91"/>
<wire x1="-129.54" y1="78.74" x2="-134.62" y2="78.74" width="0.1524" layer="91"/>
<label x="-134.62" y="78.74" size="1.778" layer="95"/>
<pinref part="D1" gate="1" pin="C"/>
<wire x1="-134.62" y1="66.04" x2="-134.62" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-134.62" y1="68.58" x2="-129.54" y2="68.58" width="0.1524" layer="91"/>
<junction x="-129.54" y="68.58"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="VIN"/>
<wire x1="58.42" y1="-33.02" x2="53.34" y2="-33.02" width="0.1524" layer="91"/>
<wire x1="53.34" y1="-33.02" x2="53.34" y2="-25.4" width="0.1524" layer="91"/>
<label x="50.8" y="-25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="D7" gate="G$1" pin="A"/>
<wire x1="78.74" y1="-121.92" x2="88.9" y2="-121.92" width="0.1524" layer="91"/>
<wire x1="88.9" y1="-121.92" x2="88.9" y2="-137.16" width="0.1524" layer="91"/>
<pinref part="L2" gate="G$1" pin="2"/>
<wire x1="88.9" y1="-137.16" x2="86.36" y2="-137.16" width="0.1524" layer="91"/>
<pinref part="R19" gate="G$1" pin="2"/>
<wire x1="86.36" y1="-137.16" x2="83.82" y2="-137.16" width="0.1524" layer="91"/>
<wire x1="86.36" y1="-139.7" x2="86.36" y2="-137.16" width="0.1524" layer="91"/>
<junction x="86.36" y="-137.16"/>
<wire x1="88.9" y1="-137.16" x2="99.06" y2="-137.16" width="0.1524" layer="91"/>
<junction x="88.9" y="-137.16"/>
<pinref part="C18" gate="G$1" pin="+"/>
<wire x1="99.06" y1="-139.7" x2="99.06" y2="-137.16" width="0.1524" layer="91"/>
<junction x="99.06" y="-137.16"/>
<pinref part="C19" gate="G$1" pin="+"/>
<wire x1="106.68" y1="-139.7" x2="106.68" y2="-137.16" width="0.1524" layer="91"/>
<wire x1="106.68" y1="-137.16" x2="99.06" y2="-137.16" width="0.1524" layer="91"/>
<wire x1="106.68" y1="-137.16" x2="116.84" y2="-137.16" width="0.1524" layer="91"/>
<junction x="106.68" y="-137.16"/>
<label x="116.84" y="-134.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="OK1" gate="G$1" pin="AC2"/>
<wire x1="210.82" y1="50.8" x2="218.44" y2="50.8" width="0.1524" layer="91"/>
<pinref part="R13" gate="G$1" pin="2"/>
</segment>
</net>
<net name="MCU_TX" class="0">
<segment>
<pinref part="R13" gate="G$1" pin="1"/>
<wire x1="228.6" y1="50.8" x2="238.76" y2="50.8" width="0.1524" layer="91"/>
<label x="241.3" y="50.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="TX"/>
<wire x1="58.42" y1="-43.18" x2="48.26" y2="-43.18" width="0.1524" layer="91"/>
<label x="43.18" y="-43.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="OK2" gate="G$1" pin="AC2"/>
<wire x1="213.36" y1="-68.58" x2="220.98" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="R15" gate="G$1" pin="2"/>
</segment>
</net>
<net name="MCU_!RESET" class="0">
<segment>
<pinref part="R15" gate="G$1" pin="1"/>
<wire x1="231.14" y1="-68.58" x2="241.3" y2="-68.58" width="0.1524" layer="91"/>
<label x="243.84" y="-68.58" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="D2"/>
<wire x1="93.98" y1="-78.74" x2="104.14" y2="-78.74" width="0.1524" layer="91"/>
<label x="104.14" y="-78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="MCU_RX" class="0">
<segment>
<pinref part="R16" gate="G$1" pin="1"/>
<wire x1="220.98" y1="2.54" x2="220.98" y2="-2.54" width="0.1524" layer="91"/>
<pinref part="OK3" gate="G$1" pin="C"/>
<wire x1="220.98" y1="-2.54" x2="213.36" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="220.98" y1="-2.54" x2="241.3" y2="-2.54" width="0.1524" layer="91"/>
<label x="241.3" y="-2.54" size="1.778" layer="95"/>
<junction x="220.98" y="-2.54"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="RX"/>
<wire x1="58.42" y1="-48.26" x2="48.26" y2="-48.26" width="0.1524" layer="91"/>
<label x="43.18" y="-48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="R17" gate="G$1" pin="1"/>
<pinref part="OK3" gate="G$1" pin="AC2"/>
<wire x1="185.42" y1="-7.62" x2="190.5" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="TR1" gate="1" pin="+VE"/>
<pinref part="L1" gate="G$1" pin="1"/>
<wire x1="-91.44" y1="-50.8" x2="-86.36" y2="-50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DGND" class="0">
<segment>
<pinref part="C13" gate="G$1" pin="-"/>
<wire x1="-71.12" y1="-60.96" x2="-83.82" y2="-60.96" width="0.1524" layer="91"/>
<wire x1="-83.82" y1="-60.96" x2="-88.9" y2="-60.96" width="0.1524" layer="91"/>
<wire x1="-88.9" y1="-60.96" x2="-88.9" y2="-58.42" width="0.1524" layer="91"/>
<pinref part="TR1" gate="1" pin="-VE"/>
<wire x1="-88.9" y1="-58.42" x2="-91.44" y2="-58.42" width="0.1524" layer="91"/>
<pinref part="SUPPLY1" gate="G$1" pin="DGND"/>
<wire x1="-83.82" y1="-63.5" x2="-83.82" y2="-60.96" width="0.1524" layer="91"/>
<wire x1="-71.12" y1="-60.96" x2="-38.1" y2="-60.96" width="0.1524" layer="91"/>
<wire x1="-38.1" y1="-60.96" x2="-38.1" y2="-55.88" width="0.1524" layer="91"/>
<pinref part="DC1" gate="G$1" pin="-VIN"/>
<wire x1="-38.1" y1="-55.88" x2="-35.56" y2="-55.88" width="0.1524" layer="91"/>
<junction x="-71.12" y="-60.96"/>
<junction x="-83.82" y="-60.96"/>
</segment>
<segment>
<pinref part="OK3" gate="G$1" pin="E"/>
<wire x1="213.36" y1="-7.62" x2="220.98" y2="-7.62" width="0.1524" layer="91"/>
<wire x1="220.98" y1="-7.62" x2="220.98" y2="-12.7" width="0.1524" layer="91"/>
<pinref part="SUPPLY2" gate="G$1" pin="DGND"/>
</segment>
<segment>
<wire x1="-134.62" y1="40.64" x2="-134.62" y2="38.1" width="0.1524" layer="91"/>
<pinref part="SUPPLY3" gate="G$1" pin="DGND"/>
<pinref part="T1" gate="G1" pin="E"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="GND@2"/>
<wire x1="58.42" y1="-38.1" x2="48.26" y2="-38.1" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-38.1" x2="48.26" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-30.48" x2="43.18" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="43.18" y1="-30.48" x2="43.18" y2="-33.02" width="0.1524" layer="91"/>
<pinref part="SUPPLY4" gate="G$1" pin="DGND"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="GND@21"/>
<wire x1="93.98" y1="-48.26" x2="106.68" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="106.68" y1="-48.26" x2="106.68" y2="-50.8" width="0.1524" layer="91"/>
<pinref part="SUPPLY5" gate="G$1" pin="DGND"/>
</segment>
</net>
<net name="LOAD" class="0">
<segment>
<pinref part="K1" gate="G$1" pin="DS2"/>
<wire x1="-109.22" y1="60.96" x2="-101.6" y2="60.96" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="60.96" x2="-101.6" y2="53.34" width="0.1524" layer="91"/>
<label x="-104.14" y="50.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="!MCU_ON" class="0">
<segment>
<wire x1="-139.7" y1="45.72" x2="-149.86" y2="45.72" width="0.1524" layer="91"/>
<label x="-154.94" y="45.72" size="1.778" layer="95"/>
<pinref part="T1" gate="G1" pin="B"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="D1"/>
<wire x1="93.98" y1="-83.82" x2="104.14" y2="-83.82" width="0.1524" layer="91"/>
<label x="104.14" y="-83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="K1" gate="G$1" pin="K"/>
<wire x1="-129.54" y1="60.96" x2="-129.54" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-129.54" y1="58.42" x2="-129.54" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-129.54" y1="50.8" x2="-134.62" y2="50.8" width="0.1524" layer="91"/>
<pinref part="T1" gate="G1" pin="C"/>
<pinref part="D1" gate="1" pin="A"/>
<wire x1="-134.62" y1="60.96" x2="-134.62" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-134.62" y1="58.42" x2="-129.54" y2="58.42" width="0.1524" layer="91"/>
<junction x="-129.54" y="58.42"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="R10" gate="G$1" pin="2"/>
<pinref part="C14" gate="A" pin="1"/>
<wire x1="-55.88" y1="-124.46" x2="-53.34" y2="-124.46" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="C14" gate="A" pin="2"/>
<pinref part="U$3" gate="G$1" pin="A"/>
<wire x1="-45.72" y1="-124.46" x2="-43.18" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="-124.46" x2="-43.18" y2="-127" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="-124.46" x2="-25.4" y2="-124.46" width="0.1524" layer="91"/>
<junction x="-43.18" y="-124.46"/>
<wire x1="-27.94" y1="-129.54" x2="-25.4" y2="-129.54" width="0.1524" layer="91"/>
<wire x1="-25.4" y1="-129.54" x2="-20.32" y2="-129.54" width="0.1524" layer="91"/>
<wire x1="-25.4" y1="-124.46" x2="-25.4" y2="-129.54" width="0.1524" layer="91"/>
<junction x="-25.4" y="-129.54"/>
<pinref part="D2" gate="G$1" pin="A"/>
<pinref part="D4" gate="G$1" pin="C"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="C"/>
<pinref part="U$3" gate="G$1" pin="C"/>
<wire x1="-43.18" y1="-142.24" x2="-43.18" y2="-132.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<wire x1="-15.24" y1="-129.54" x2="-10.16" y2="-129.54" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="-129.54" x2="-10.16" y2="-142.24" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="-142.24" x2="-15.24" y2="-142.24" width="0.1524" layer="91"/>
<pinref part="C15" gate="G$1" pin="+"/>
<wire x1="-10.16" y1="-144.78" x2="-10.16" y2="-142.24" width="0.1524" layer="91"/>
<junction x="-10.16" y="-142.24"/>
<pinref part="R18" gate="G$1" pin="2"/>
<wire x1="0" y1="-129.54" x2="-10.16" y2="-129.54" width="0.1524" layer="91"/>
<junction x="-10.16" y="-129.54"/>
<pinref part="D2" gate="G$1" pin="C"/>
<pinref part="D3" gate="G$1" pin="C"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="C"/>
<pinref part="R18" gate="G$1" pin="1"/>
<wire x1="0" y1="-144.78" x2="0" y2="-142.24" width="0.1524" layer="91"/>
<wire x1="0" y1="-142.24" x2="0" y2="-139.7" width="0.1524" layer="91"/>
<junction x="0" y="-142.24"/>
<pinref part="U1" gate="A" pin="VIN"/>
<wire x1="0" y1="-142.24" x2="7.62" y2="-142.24" width="0.1524" layer="91"/>
<pinref part="C16" gate="G$1" pin="+"/>
<wire x1="7.62" y1="-142.24" x2="15.24" y2="-142.24" width="0.1524" layer="91"/>
<wire x1="15.24" y1="-142.24" x2="27.94" y2="-142.24" width="0.1524" layer="91"/>
<wire x1="7.62" y1="-144.78" x2="7.62" y2="-142.24" width="0.1524" layer="91"/>
<junction x="7.62" y="-142.24"/>
<pinref part="U1" gate="A" pin="EN"/>
<wire x1="27.94" y1="-149.86" x2="15.24" y2="-149.86" width="0.1524" layer="91"/>
<wire x1="15.24" y1="-149.86" x2="15.24" y2="-142.24" width="0.1524" layer="91"/>
<junction x="15.24" y="-142.24"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="D6" gate="G$1" pin="C"/>
<wire x1="66.04" y1="-139.7" x2="66.04" y2="-137.16" width="0.1524" layer="91"/>
<pinref part="L2" gate="G$1" pin="1"/>
<wire x1="66.04" y1="-137.16" x2="68.58" y2="-137.16" width="0.1524" layer="91"/>
<pinref part="C17" gate="G$1" pin="1"/>
<wire x1="68.58" y1="-137.16" x2="73.66" y2="-137.16" width="0.1524" layer="91"/>
<wire x1="68.58" y1="-134.62" x2="68.58" y2="-137.16" width="0.1524" layer="91"/>
<junction x="68.58" y="-137.16"/>
<pinref part="U1" gate="A" pin="SW"/>
<wire x1="58.42" y1="-142.24" x2="58.42" y2="-137.16" width="0.1524" layer="91"/>
<wire x1="58.42" y1="-137.16" x2="66.04" y2="-137.16" width="0.1524" layer="91"/>
<junction x="66.04" y="-137.16"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="C17" gate="G$1" pin="2"/>
<wire x1="68.58" y1="-127" x2="68.58" y2="-121.92" width="0.1524" layer="91"/>
<pinref part="D7" gate="G$1" pin="C"/>
<wire x1="73.66" y1="-121.92" x2="76.2" y2="-121.92" width="0.1524" layer="91"/>
<wire x1="73.66" y1="-121.92" x2="68.58" y2="-121.92" width="0.1524" layer="91"/>
<pinref part="U1" gate="A" pin="BOOST"/>
<wire x1="68.58" y1="-121.92" x2="43.18" y2="-121.92" width="0.1524" layer="91"/>
<wire x1="43.18" y1="-121.92" x2="43.18" y2="-132.08" width="0.1524" layer="91"/>
<junction x="68.58" y="-121.92"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="U1" gate="A" pin="VFB"/>
<wire x1="58.42" y1="-152.4" x2="86.36" y2="-152.4" width="0.1524" layer="91"/>
<pinref part="R19" gate="G$1" pin="1"/>
<wire x1="86.36" y1="-152.4" x2="86.36" y2="-149.86" width="0.1524" layer="91"/>
<pinref part="R20" gate="G$1" pin="2"/>
<wire x1="86.36" y1="-152.4" x2="86.36" y2="-154.94" width="0.1524" layer="91"/>
<junction x="86.36" y="-152.4"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="R21" gate="G$1" pin="2"/>
<pinref part="D8" gate="G$1" pin="A"/>
<wire x1="-106.68" y1="-200.66" x2="-101.6" y2="-200.66" width="0.1524" layer="91"/>
<pinref part="R22" gate="G$1" pin="1"/>
<wire x1="-101.6" y1="-200.66" x2="-99.06" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="-218.44" x2="-101.6" y2="-200.66" width="0.1524" layer="91"/>
<junction x="-101.6" y="-200.66"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="D8" gate="G$1" pin="C"/>
<pinref part="L3" gate="G$1" pin="1"/>
<wire x1="-93.98" y1="-200.66" x2="-88.9" y2="-200.66" width="0.1524" layer="91"/>
<pinref part="C20" gate="G$1" pin="2"/>
<wire x1="-88.9" y1="-200.66" x2="-83.82" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="-88.9" y1="-220.98" x2="-88.9" y2="-200.66" width="0.1524" layer="91"/>
<junction x="-88.9" y="-200.66"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="C22" gate="G$1" pin="+"/>
<pinref part="C21" gate="G$1" pin="-"/>
<wire x1="-68.58" y1="-231.14" x2="-68.58" y2="-226.06" width="0.1524" layer="91"/>
<pinref part="R24" gate="G$1" pin="1"/>
<wire x1="-68.58" y1="-226.06" x2="-68.58" y2="-218.44" width="0.1524" layer="91"/>
<wire x1="-53.34" y1="-226.06" x2="-68.58" y2="-226.06" width="0.1524" layer="91"/>
<junction x="-68.58" y="-226.06"/>
<pinref part="R25" gate="G$1" pin="2"/>
<wire x1="-53.34" y1="-226.06" x2="-50.8" y2="-226.06" width="0.1524" layer="91"/>
<junction x="-53.34" y="-226.06"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="C21" gate="G$1" pin="+"/>
<wire x1="-68.58" y1="-210.82" x2="-68.58" y2="-200.66" width="0.1524" layer="91"/>
<pinref part="L3" gate="G$1" pin="2"/>
<wire x1="-68.58" y1="-200.66" x2="-73.66" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="-68.58" y1="-200.66" x2="-53.34" y2="-200.66" width="0.1524" layer="91"/>
<junction x="-68.58" y="-200.66"/>
<pinref part="R23" gate="G$1" pin="2"/>
<wire x1="-53.34" y1="-200.66" x2="-53.34" y2="-203.2" width="0.1524" layer="91"/>
<pinref part="Q1" gate="G$1" pin="C"/>
<wire x1="-33.02" y1="-200.66" x2="-53.34" y2="-200.66" width="0.1524" layer="91"/>
<junction x="-53.34" y="-200.66"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="R23" gate="G$1" pin="1"/>
<pinref part="R24" gate="G$1" pin="2"/>
<wire x1="-53.34" y1="-213.36" x2="-53.34" y2="-215.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="R25" gate="G$1" pin="1"/>
<pinref part="R26" gate="G$1" pin="2"/>
<wire x1="-40.64" y1="-226.06" x2="-38.1" y2="-226.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="R26" gate="G$1" pin="1"/>
<pinref part="U2" gate="A" pin="VDD"/>
<wire x1="-27.94" y1="-226.06" x2="-25.4" y2="-226.06" width="0.1524" layer="91"/>
<pinref part="D9" gate="G$1" pin="C"/>
<wire x1="-27.94" y1="-251.46" x2="-27.94" y2="-226.06" width="0.1524" layer="91"/>
<junction x="-27.94" y="-226.06"/>
<pinref part="C23" gate="G$1" pin="+"/>
<wire x1="-27.94" y1="-251.46" x2="-15.24" y2="-251.46" width="0.1524" layer="91"/>
<junction x="-27.94" y="-251.46"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="U2" gate="A" pin="DRV"/>
<wire x1="-25.4" y1="-218.44" x2="-27.94" y2="-218.44" width="0.1524" layer="91"/>
<pinref part="Q1" gate="G$1" pin="B"/>
<wire x1="-27.94" y1="-218.44" x2="-27.94" y2="-205.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$36" class="0">
<segment>
<pinref part="U2" gate="A" pin="CS"/>
<wire x1="5.08" y1="-218.44" x2="5.08" y2="-200.66" width="0.1524" layer="91"/>
<pinref part="Q1" gate="G$1" pin="E"/>
<wire x1="5.08" y1="-200.66" x2="-22.86" y2="-200.66" width="0.1524" layer="91"/>
<pinref part="R27" gate="G$1" pin="2"/>
<wire x1="7.62" y1="-200.66" x2="5.08" y2="-200.66" width="0.1524" layer="91"/>
<junction x="5.08" y="-200.66"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="U2" gate="A" pin="GND"/>
<wire x1="5.08" y1="-226.06" x2="17.78" y2="-226.06" width="0.1524" layer="91"/>
<wire x1="17.78" y1="-226.06" x2="17.78" y2="-251.46" width="0.1524" layer="91"/>
<pinref part="C23" gate="G$1" pin="-"/>
<wire x1="17.78" y1="-251.46" x2="-7.62" y2="-251.46" width="0.1524" layer="91"/>
<pinref part="R27" gate="G$1" pin="1"/>
<wire x1="17.78" y1="-200.66" x2="17.78" y2="-226.06" width="0.1524" layer="91"/>
<junction x="17.78" y="-226.06"/>
<pinref part="R28" gate="G$1" pin="1"/>
<wire x1="15.24" y1="-261.62" x2="17.78" y2="-261.62" width="0.1524" layer="91"/>
<wire x1="17.78" y1="-261.62" x2="17.78" y2="-251.46" width="0.1524" layer="91"/>
<junction x="17.78" y="-251.46"/>
<pinref part="L4" gate="G$1" pin="1"/>
<wire x1="27.94" y1="-200.66" x2="25.4" y2="-200.66" width="0.1524" layer="91"/>
<junction x="17.78" y="-200.66"/>
<pinref part="D10" gate="G$1" pin="C"/>
<wire x1="25.4" y1="-200.66" x2="17.78" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="25.4" y1="-226.06" x2="25.4" y2="-200.66" width="0.1524" layer="91"/>
<junction x="25.4" y="-200.66"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="R28" gate="G$1" pin="2"/>
<pinref part="R29" gate="G$1" pin="1"/>
<wire x1="5.08" y1="-261.62" x2="-20.32" y2="-261.62" width="0.1524" layer="91"/>
<pinref part="U2" gate="A" pin="VS"/>
<wire x1="5.08" y1="-261.62" x2="5.08" y2="-233.68" width="0.1524" layer="91"/>
<junction x="5.08" y="-261.62"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="R29" gate="G$1" pin="2"/>
<wire x1="-30.48" y1="-261.62" x2="-38.1" y2="-261.62" width="0.1524" layer="91"/>
<wire x1="-38.1" y1="-261.62" x2="-38.1" y2="-251.46" width="0.1524" layer="91"/>
<pinref part="D9" gate="G$1" pin="A"/>
<wire x1="-38.1" y1="-251.46" x2="-33.02" y2="-251.46" width="0.1524" layer="91"/>
<wire x1="-38.1" y1="-251.46" x2="-38.1" y2="-195.58" width="0.1524" layer="91"/>
<junction x="-38.1" y="-251.46"/>
<wire x1="-38.1" y1="-195.58" x2="40.64" y2="-195.58" width="0.1524" layer="91"/>
<wire x1="40.64" y1="-195.58" x2="40.64" y2="-200.66" width="0.1524" layer="91"/>
<pinref part="L4" gate="G$1" pin="2"/>
<wire x1="40.64" y1="-200.66" x2="38.1" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="40.64" y1="-223.52" x2="40.64" y2="-200.66" width="0.1524" layer="91"/>
<junction x="40.64" y="-200.66"/>
<pinref part="R30" gate="G$1" pin="1"/>
<wire x1="55.88" y1="-220.98" x2="55.88" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="55.88" y1="-200.66" x2="40.64" y2="-200.66" width="0.1524" layer="91"/>
<pinref part="C25" gate="G$1" pin="2"/>
<wire x1="71.12" y1="-223.52" x2="71.12" y2="-200.66" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-200.66" x2="55.88" y2="-200.66" width="0.1524" layer="91"/>
<junction x="55.88" y="-200.66"/>
<wire x1="71.12" y1="-200.66" x2="119.38" y2="-200.66" width="0.1524" layer="91"/>
<junction x="71.12" y="-200.66"/>
<pinref part="C26" gate="G$1" pin="+"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="104,1,63.5,68.58,U$1,VDDD,N$5,,,"/>
<approved hash="104,1,317.5,15.24,U$2,VIN,+5V,,,"/>
<approved hash="104,1,317.5,10.16,U$2,GND,DGND,,,"/>
<approved hash="204,1,353.06,15.24,U$2,3V3,,,,"/>
<approved hash="204,1,353.06,5.08,U$2,VBAT,,,,"/>
<approved hash="104,1,353.06,0,U$2,GND,DGND,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
