#include "web.hpp"
#include "opensound.h"
#include "application.h"
#include "ApplicationSettings.h"

#if 0 // static
int32_t process_cvgate(const char* u, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){		       
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>CV/Gate</h1>"
	 << "<input type='range' id='cva' min='-1' max='1' step='0.1'/>"
	 << "<br><button id='tra'>A</button>"
	 << "<br><input type='range' id='cvb' min='-1' max='1' step='0.1'/>"
	 << "<br><button id='trb'>B</button>"
	 << "<script>function cv(i,v){var rq=new XMLHttpRequest();rq.open('GET', '/cvout'+i+'?v='+v);rq.send(null);};"
	 << "function tr(i){var rq=new XMLHttpRequest();rq.open('GET', '/trout'+i);rq.send(null);};"
	 << "document.getElementById('cva').onchange=function(){cv(0,this.value)};"
	 << "document.getElementById('tra').onclick=function(){tr(0)};"
	 << "document.getElementById('cvb').onchange=function(){cv(1,this.value)};"
	 << "document.getElementById('trb').onclick=function(){tr(1)}</script>"
	 << OSM_BACK << OSM_END;
  return 0;
}
#endif
    
int32_t process_cvout(const char* u, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  UrlScanner url(u);
  float v;
  const char* param = url.getParameter("v");
  if(v != NULL)
    v = atof(param);
  if((int)arg == 0)
    setCVA(v);
  else if((int)arg == 1)
    setCVB(v);
  return 0;
}

int32_t process_trout(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  if((int)arg == 0)
    toggleTriggerA();
  else if((int)arg == 1)
    toggleTriggerB();
  return 0;
}
