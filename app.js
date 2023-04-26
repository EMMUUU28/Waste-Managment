const express=require("express");
const app=express();
const https = require("https")
const bodyParser=require("body-parser");
const { channel } = require("diagnostics_channel");
app.use(express.static("public"))
app.use(bodyParser.urlencoded({extended:true}));
app.get("/index.html",function(req,res)
{
    res.sendFile(__dirname+"/index.html")
})

app.post("/services.html",function(req,res)
{

       console.log("clicked Services")
        https.get("https://api.thingspeak.com/channels/2037930/feeds.json?api_key=SG6DOTVB73FNYXGB&results=1",function(response)
        {
        console.log(response.statusCode)
        response.on("data",function(data){
            const info=JSON.parse(data)
            console.log(info.channel.field1+" bin is: "+ info.feeds[0].field1+" filled.")
            res.write("<h1>"+info.channel.field2+" bin is: "+Math.round( ((15-info.feeds[0].field2)/15)*100)+" % filled.</h1>")
            res.write("<h1>"+info.channel.field1+" bin is: "+Math.round( ((15-info.feeds[0].field1)/15)*100)+" % filled.</h1>")
            res.write("<h1>The location of the dustbin is "+info.channel.latitude+" latitude and " +info.channel.longitude+" longitude</h1>")
            
        })
    })
})
 
app.listen(3000,function(){
    console.log("Server is running..")
})
