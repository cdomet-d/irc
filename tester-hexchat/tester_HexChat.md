# Guide testing HexChat

This will be a user guide on how to use the Python scripts testing for our IRC server using HexChat as a reference client.

## Scripts for HexChat

### Step 1 : Addons file
The first step will be find the addons folder in the HexChat's folder. Scripts will need to be placed inside of that folder before being loaded onto HexChat\
In Linux, look for :

```
~/.config/hexchat/addons
```
Create the folder if it doesn't exist.

You will also need to check Python installed and enabled in HexChat before you try to add Python scripts.
To check, open a `HexChat window`, connect to your server. Open 
```
Window > Plugins and Scripts
```
If Python is available in HexChat, you will see :

[HexChat_python_enabled](PythonCheckIrc.png)

### Step 2 : Writing scritps
HexChat will (normally) supported scripts in Lua or in Python, so feel free to explore.

### Step 3 : Load scripts in HexChat
To load scripts in HexChat, first open a window and connect to your server.
Go to :
```
Window > Plugins and Scripts
```
Click on `Load` and select your scripts. 

You can also simply restart HexChat and all the scripts in the `addons` folder will be load and/or reload automatically


## Using my scripts
Unfortunalty, HexChat isn't as malleable as we wish it was.\
We will need to create client with specific `nickname`, or channels with a specific `name` for the scripts to be executed the way we want it to.\
This will be a comprehensive guide on how to set up HexChat to test your IRC server (almost) automatically.

### Who
script : `who.py`

Step to use the script:
```
Connect first client
Create channel with name: 'testwho'

Connect second client
Join channel 'testwho'
```

### Nick
script : `nick.py`

Step to use the script
```
Connect first client
Create channel with name: 'testnick'

Connect second client
Join channel 'testnick'
```
### Join

### Mode

### Topic

### Privmsg

### Invite

### Kick

### Part

### Quit





