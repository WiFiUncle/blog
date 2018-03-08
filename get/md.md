```
function query(q) {
	var args = {};
	var queryStr = location.search ? location.search.substring(1) : "";
   var items = queryStr.split("&");
 var len = items.length;
   var key = '';
  var v = '';
  var item = ''
 for(var i = 0; i < len; i ++) {
		item = items[i].split("=");
        key = decodeURIComponent(item[0]);
        v = decodeURIComponent(item[1]);
      args[key] = v;		
  } 
  console.log(args);
	
}
query();

```