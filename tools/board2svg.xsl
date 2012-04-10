<?xml version="1.0" encoding="utf-8"?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
	       xmlns:svg="http://www.w3.org/2000/svg"
	       xmlns:exslt="http://exslt.org/common"
	       xmlns="http://www.w3.org/2000/svg" >


  <xsl:output method="xml" indent="yes"/>

  <xsl:variable name="boards" select="document('boards.xml')"/>

<!--   <xsl:variable name="boards"> -->
<!--     <boards> -->
<!--     <board name="4hp" width="20.00" height="128.50"> -->
<!--       <svg:circle cx="7.5" cy="3" r="1.6"/> -->
<!--     </board> -->
<!--     <board name="6hp" width="30.00" height="128.50"> -->
<!--       <svg:circle cx="7.5" cy="3" r="1.6"/> -->
<!--     </board> -->
<!--     <board name="10hp" width="50.50" height="128.50"> -->
<!--       <svg:circle cx="7.5" cy="3" r="1.6"/> -->
<!--       <svg:circle cx="43.06" cy="3" r="1.6"/> -->
<!--     </board> -->
<!--     </boards> -->
<!--   </xsl:variable> -->

  <xsl:variable name="board" select="$boards/boards/board[@name=current()/board/@type]"/>
  <xsl:variable name="width" select="$board/@width"/>
  <xsl:variable name="height" select="$board/@height"/>
<!--   <xsl:variable name="width" select="$boards/boards/board[@name=$board]/@width"/> -->
<!--   <xsl:variable name="height" select="$boards/boards/board[@name=$board]/@height"/> -->
<!--   <xsl:variable name="width" select="exslt:node-set($boards)/board[@name=$board]/@width"/> -->
<!--   <xsl:variable name="height" select="exslt:node-set($boards)/board[@name=$board]/@height"/> -->

  <xsl:variable name="inch" select="25.4"/>

  <xsl:template match="/">
  <xsl:message>width <xsl:value-of select="$width"/></xsl:message>
    <svg
       xmlns:dc="http://purl.org/dc/elements/1.1/"
       xmlns:cc="http://creativecommons.org/ns#"
       xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
       xmlns:svg="http://www.w3.org/2000/svg"
       xmlns="http://www.w3.org/2000/svg"
       version="1.1"
       width="210mm"
       height="297mm"
       viewBox="0 0 210 297"
       id="svg16476">
      <metadata id="metadata4">     
	<rdf:RDF>
	  <cc:Work
             rdf:about="">
            <dc:format>image/svg+xml</dc:format>
            <dc:type
               rdf:resource="http://purl.org/dc/dcmitype/StillImage" />
            <dc:title></dc:title>
	  </cc:Work>
	</rdf:RDF>
      </metadata>
      <xsl:apply-templates select="board"/>

    </svg>
  </xsl:template>

  <xsl:template match="board">
    <xsl:message>hello board</xsl:message>
    <xsl:variable name="type" select="@type"/>
    <g id="board1" 
       style="fill:none;stroke-width:0.1;stroke:black">
      <rect x="0.0" y="0.0" width="{$width}" height="{$height}"/>
      <xsl:copy-of select="$board/*"/> 
      <xsl:apply-templates/>
    </g>
  </xsl:template>

  <xsl:template match="hole">
    <circle cx="{$width div 2+@x*$inch}"
	    cy="{$height div 2-@y*$inch}"
	    r="{@radius}"/>

  </xsl:template>

</xsl:transform>
