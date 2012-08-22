<?xml version="1.0" encoding="utf-8"?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
	       xmlns:svg="http://www.w3.org/2000/svg"
	       xmlns:exslt="http://exslt.org/common"
	       xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
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
       xmlns:svg="http://www.w3.org/2000/svg" version="1.1"
	 width="210mm" height="297mm"
	 viewBox="0 0 210 297">
      <xsl:apply-templates select="module"/>
    </svg>
  </xsl:template>

  <xsl:template match="module">
    <xsl:variable name="type" select="@type"/>
    <g style="fill:none;stroke-width:0.1;stroke:black">
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

  <xsl:template match="pot">
  <path
     d="m {$width div 2+@x*$inch},{$height div 2 - @y*$inch - 4.75} c -2.6220187,0 -4.7546972,2.123364 -4.7546972,4.745368 0,2.143796 1.4261951,3.960351 3.3776012,4.54998 l 0,2.679746 2.642536,0 0,-2.651834 c 2.003484,-0.55658 3.479956,-2.397067 3.479956,-4.577892 0,-2.622004 -2.123369,-4.745368 -4.745396,-4.745368 z"
     style="fill:none;stroke:#000000;stroke-width:0.09990668;"
     inkscape:connector-curvature="0" />
  </xsl:template>

  <xsl:template match="svg:*">
    <xsl:copy-of select="."/>
  </xsl:template>

</xsl:transform>
