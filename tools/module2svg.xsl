<?xml version="1.0" encoding="utf-8"?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
	       xmlns:svg="http://www.w3.org/2000/svg"
	       xmlns:exslt="http://exslt.org/common"
	       xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
	       xmlns:xlink="http://www.w3.org/1999/xlink"
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
	 xmlns:xlink="http://www.w3.org/1999/xlink"
	 xmlns:svg="http://www.w3.org/2000/svg" version="1.1"
	 width="210mm" height="297mm"
	 viewBox="0 0 210 297">
      <defs>
	<g id="potgrading">
	  <path
	     d="M 22.469177,65.29487 C 12.864593,59.897939 6.3758317,49.616792 6.3758317,37.815007 c 0,-17.395119 14.1022403,-31.4975588 31.4994303,-31.4975588 17.392315,0 31.496992,14.1012398 31.496992,31.4975588 0,11.809085 -6.498509,22.101133 -16.116497,27.493263"
	     style="fill:none;stroke:#030303;stroke-width:0.41032487" />
	  <path
	     d="m 28.906759,4.4567034 0.78974,2.9366707"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="M 19.149856,5.4303268 22.099957,10.54465"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="m 13.42878,13.404619 2.150735,2.149652"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="m 5.5191934,19.159858 5.0557506,2.91857"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="m 4.4968328,28.890192 2.9366973,0.786019"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="m 0.49999997,37.829608 5.86364623,0"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="M 4.5053627,46.769023 7.44206,45.980604"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="M 5.5106636,56.509058 10.590785,53.578387"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="m 13.451932,62.247196 2.145861,-2.149452"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="m 19.291208,70.009583 2.834339,-4.907218"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="m 56.484784,70.043684 -2.861026,-4.95962"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="M 62.293717,62.224096 60.144201,60.079444"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="m 70.111912,56.418856 -4.965577,-2.86977"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="M 71.224445,46.738522 68.290307,45.951403"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="m 75.037277,37.799107 -5.678427,0"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="M 71.216037,28.859791 68.280436,29.64821"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="m 70.076574,19.198959 -4.943643,2.855068"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="M 62.27288,13.382718 60.124704,15.53107"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="M 56.550707,5.4181265 53.598168,10.52765"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="M 46.785274,4.4507032 45.999312,7.386174"
	     style="fill:none;stroke:#030303;stroke-width:0.75" />
	  <path
	     d="m 37.844676,0.500008 0,5.8162402"
	     style="fill:none;stroke:#030303;stroke-width:1.0" />
	  <path
	     d="m 69.475831,37.723605 c 0,17.397619 -14.103337,31.501159 -31.500648,31.501159 -17.397312,0 -31.500649,-14.10354 -31.500649,-31.501159 0,-17.397619 14.103337,-31.5012591 31.500649,-31.5012591 17.397311,0 31.500648,14.1036401 31.500648,31.5012591 z"
	     style="fill:none" />
	</g>
      </defs>
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

  <xsl:template match="rect">
    <rect x="{$width div 2 + @x*$inch - @width div 2}"
	  y="{$height div 2 - @y*$inch - @height div 2}"
	  width="{@width}" 
	  height="{@height}"/>
  </xsl:template>

  <xsl:template match="pot">
  <path
     d="m {$width div 2+@x*$inch},{$height div 2 - @y*$inch - 4.75} c -2.6220187,0 -4.7546972,2.123364 -4.7546972,4.745368 0,2.143796 1.4261951,3.960351 3.3776012,4.54998 l 0,2.679746 2.642536,0 0,-2.651834 c 2.003484,-0.55658 3.479956,-2.397067 3.479956,-4.577892 0,-2.622004 -2.123369,-4.745368 -4.745396,-4.745368 z"
     style="fill:none;stroke:#000000;stroke-width:0.09990668;"
     inkscape:connector-curvature="0" />
  <g transform="translate({$width div 2+@x*$inch},{$height div 2 - @y*$inch})"
     style="fill:none;stroke:#000000;stroke-width:0.237;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none">
  <path
     d="M -4.2037748,7.5814929 C -6.8346316,6.1114925 -8.6120123,3.3014922 -8.6120123,0.07148931 c 0,-4.75000381 3.8628404,-8.61000481 8.6282233,-8.61000481 4.764047,0 8.627555,3.8600011 8.627555,8.61000481 0,3.23000299 -1.780051,6.04000329 -4.414579,7.52000359" 
     style="fill:none;stroke:#030303;stroke-width:0.1411" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117"
     d="m -2.440413,-9.0485165 0.216323,0.810001" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832" 
     d="m -5.1129926,-8.7785155 0.8080822,1.4000001" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117"
     d="m -6.6800914,-6.5985155 0.5891225,0.59" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832" 
     d="m -8.8466601,-5.0285155 1.3848552,0.8000013" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117"
     d="m -9.1267017,-2.3685125 0.8044106,0.2200004" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832" 
     d="m -10.221501,0.08148931 1.6061507,0" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117"
     d="M -9.1243652,2.5214918 -8.3199546,2.3014913" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832" 
     d="M -8.8489964,5.181492 -7.4574658,4.3814921" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117"
     d="m -6.6737496,6.7514925 0.5877873,-0.59" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832" 
     d="m -5.0742739,8.871494 0.776373,-1.3400011" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832"
     d="M 5.113671,8.8814939 4.329988,7.5214929" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117" 
     d="m 6.704836,6.7414925 -0.588789,-0.58" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832"
     d="m 8.846371,5.1614921 -1.360155,-0.79" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117" 
     d="M 9.151112,2.5114918 8.347402,2.2914913" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832"
     d="m 10.195511,0.07148931 -1.555417,0" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117" 
     d="M 9.148809,-2.3785126 8.344698,-2.1585121" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832"
     d="M 8.836691,-5.0185155 7.482544,-4.2385142" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117" 
     d="m 6.699128,-6.6085155 -0.588421,0.59" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832"
     d="m 5.131729,-8.7785155 -0.80875,1.39" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2117" 
     d="m 2.456813,-9.0485165 -0.215288,0.800001" />
  <path style="fill:none;stroke:#030303;stroke-width:0.2832"
     d="m 0.007833,-10.128517 0,1.5900015" />
  </g>
<!--   <use x="{$width div 2+@x*$inch}" y="{$height div 2-@y*$inch}" xlink:href="#potgrading"/> -->
  </xsl:template>

  <xsl:template match="svg:*">
    <xsl:copy-of select="."/>
  </xsl:template>

</xsl:transform>
