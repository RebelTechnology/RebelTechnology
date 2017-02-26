<?xml version="1.0" encoding="utf-8"?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
	       xmlns:svg="http://www.w3.org/2000/svg"
	       xmlns:exslt="http://exslt.org/common"
	       xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
	       xmlns:xlink="http://www.w3.org/1999/xlink"
	       xmlns="http://www.w3.org/2000/svg" 
	 xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd">

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
	 xmlns:xlink="http://www.w3.org/1999/xlink"
	 xmlns:svg="http://www.w3.org/2000/svg" version="1.1"
	 xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
	 xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
	 width="210mm" height="297mm"
	 viewBox="0 0 210 297">
  <sodipodi:namedview
     id="base"
     inkscape:document-units="mm"
     units="mm"/>
      <defs>
  	<g id="potgrading">
	</g>
      </defs>
      <xsl:apply-templates select="module"/>
    </svg>
  </xsl:template>

  <xsl:template match="module">
    <xsl:variable name="type" select="@type"/>
    <g style="fill:none;stroke-width:0.05;stroke:#ff0000">
      <rect x="0.0" y="0.0" width="{$width}" height="{$height}"/>
      <xsl:copy-of select="$module/*"/> 
      <xsl:apply-templates/>
    </g>
  </xsl:template>

  <xsl:template match="hole">
    <circle cx="{$width div 2+@x*$inch}"
	    cy="{$height div 2-@y*$inch}"
	    r="{@radius}"
	    style="fill:none;stroke:#ff0000" />
  </xsl:template>

  <xsl:template match="rect">
    <rect x="{$width div 2 + @x*$inch - @width div 2}"
	  y="{$height div 2 - @y*$inch - @height div 2}"
	  width="{@width}" 
	  height="{@height}"
	  style="fill:none;stroke:#ff0000" />
  </xsl:template>

  <xsl:template name="grading">
    <xsl:param name="style" select="'normal'"/>
    <xsl:variable name="scale">
      <xsl:choose>
	<xsl:when test="$style[1] = 'small'">0.78</xsl:when>
	<xsl:otherwise>1.0</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <!-- <xsl:message>scale: <xsl:value-of select="$scale"/></xsl:message> -->
    <!-- <xsl:message>grading: <xsl:value-of select="$style"/></xsl:message> -->
    <xsl:if test="not($style = 'none')">
      <g transform="translate({$width div 2+@x*$inch},{$height div 2 - @y*$inch})">
	<g transform="scale({$scale})">
	  <!--   <use xlink:href="#potgrading"/> -->
	  <path style="fill:none;stroke:#030303;stroke-width:0.212"
		d="M -4.2037748,7.5814929 C -6.8346316,6.1114925 -8.6120123,3.3014922 -8.6120123,0.07148931 c 0,-4.75000381 3.8628404,-8.61000481 8.6282233,-8.61000481 4.764047,0 8.627555,3.8600011 8.627555,8.61000481 0,3.23000299 -1.780051,6.04000329 -4.414579,7.52000359" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212"
		d="m -2.440413,-9.0485165 0.216323,0.810001" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283" 
		d="m -5.1129926,-8.7785155 0.8080822,1.4000001" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212"
		d="m -6.6800914,-6.5985155 0.5891225,0.59" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283" 
		d="m -8.8466601,-5.0285155 1.3848552,0.8000013" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212"
		d="m -9.1267017,-2.3685125 0.8044106,0.2200004" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283" 
		d="m -10.221501,0.08148931 1.6061507,0" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212"
		d="M -9.1243652,2.5214918 -8.3199546,2.3014913" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283" 
		d="M -8.8489964,5.181492 -7.4574658,4.3814921" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212"
		d="m -6.6737496,6.7514925 0.5877873,-0.59" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283" 
		d="m -5.0742739,8.871494 0.776373,-1.3400011" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283"
		d="M 5.113671,8.8814939 4.329988,7.5214929" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212" 
		d="m 6.704836,6.7414925 -0.588789,-0.58" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283"
		d="m 8.846371,5.1614921 -1.360155,-0.79" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212" 
		d="M 9.151112,2.5114918 8.347402,2.2914913" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283"
		d="m 10.195511,0.07148931 -1.555417,0" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212" 
		d="M 9.148809,-2.3785126 8.344698,-2.1585121" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283"
		d="M 8.836691,-5.0185155 7.482544,-4.2385142" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212" 
		d="m 6.699128,-6.6085155 -0.588421,0.59" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283"
		d="m 5.131729,-8.7785155 -0.80875,1.39" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.212" 
		d="m 2.456813,-9.0485165 -0.215288,0.800001" />
	  <path style="fill:none;stroke:#030303;stroke-width:0.283"
		d="m 0.007833,-10.128517 0,1.5900015" />
	</g>
      </g>
    </xsl:if>
  </xsl:template>

  <xsl:template match="pot" mode="PTD90">
    <!-- Bourns PTD901 / PTD902 -->
    <!-- cut path for right angle M7 pot with rotation stop -->
    <path inkscape:connector-curvature="0"
	  d="m {$width div 2+@x*$inch - 3.626},{$height div 2 - @y*$inch} c 0,2.002 1.6212268,3.62994 3.6230338,3.62994 1.6368275,0 3.0237835,-1.08879 3.4738775,-2.57831 l 2.868088,0 0,-2.01736 -2.846884,0 c -0.425034,-1.52937 -1.830243,-2.6564 -3.4953613,-2.6564 -2.0018076,-2.6e-4 -3.622754,1.62066 -3.622754,3.62213 z"
       style="fill:none;stroke:#ff0000" />
  </xsl:template>

  <xsl:template match="pot" mode="RK09">
    <!-- Alps RK09L -->
    <!-- cut path for M9 pot with rotation stop -->
    <path inkscape:connector-curvature="0"
	  d="m {$width div 2+@x*$inch},{$height div 2 - @y*$inch - 4.75} c -2.6129013,0 -4.7375971,2.115556 -4.7375971,4.727735 0,2.135913 1.421033,3.945767 3.3650681,4.5331 l 0,2.107204 2.632936,1.41e-4 0,-2.079677 c 1.996054,-0.554631 3.466996,-2.388302 3.466996,-4.561134 3.38e-4,-2.612179 -2.115205,-4.727369 -4.727403,-4.727369 z"
       style="fill:none;stroke:#ff0000" />
  </xsl:template>

  <xsl:template match="pot">
    <xsl:choose>
      <xsl:when test="@type = 'M7'">
	<xsl:apply-templates select="." mode="PTD90"/>
      </xsl:when>
      <xsl:otherwise>
	<xsl:apply-templates select="." mode="RK09"/>
      </xsl:otherwise>
    </xsl:choose>

    <xsl:call-template name="grading">
      <xsl:with-param name="style" select="/module/@grading|@grading"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="svg:*">
    <xsl:copy-of select="."/>
  </xsl:template>

</xsl:transform>
