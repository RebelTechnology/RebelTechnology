<?xml version="1.0" encoding="utf-8"?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
	       xmlns:svg="http://www.w3.org/2000/svg"
	       xmlns:exslt="http://exslt.org/common"
	       xmlns="http://www.w3.org/2000/svg" >


  <xsl:output method="xml" indent="yes"/>

  <xsl:variable name="modules" select="document('modules.xml')"/>

  <xsl:variable name="module" select="$modules/modules/module[@name=current()/module/@type]"/>
  <xsl:variable name="width" select="$module/@width"/>
  <xsl:variable name="height" select="$module/@height"/>

  <xsl:variable name="inch" select="25.4"/>

  <xsl:template match="/">
    <svg xmlns="http://www.w3.org/2000/svg"
       xmlns:dc="http://purl.org/dc/elements/1.1/"
       xmlns:cc="http://creativecommons.org/ns#"
       xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
       xmlns:svg="http://www.w3.org/2000/svg"
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
      <xsl:apply-templates select="module"/>
    </svg>
  </xsl:template>

  <xsl:template match="module">
    <xsl:message>hello module</xsl:message>
    <xsl:variable name="type" select="@type"/>
    <g id="module1" 
       style="fill:none;stroke-width:0.1;stroke:black">
      <rect x="0.0" y="0.0" width="{$width}" height="{$height}"/>
      <xsl:copy-of select="$module/*"/> 
      <xsl:apply-templates/>
    </g>
  </xsl:template>

  <xsl:template match="hole">
    <circle cx="{$width div 2+@x*$inch}"
	    cy="{$height div 2-@y*$inch}"
	    r="{@radius}"/>

  </xsl:template>

</xsl:transform>
