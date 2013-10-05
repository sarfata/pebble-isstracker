# ISS Tracker

A Pebble sample project that shows next pass of the Internation Space Station over your head!

## Usage

To compile this program you can choose one of the following option:


 * Using Cloud Pebble
 ** Fork this project on github
 ** Create an account on cloudpebble
 ** Compile this project

 * Install the Pebble SDK and compile on your computer
 ** Follow instructions on [Pebble Developer site](http://developer.getpebble.com) to install Pebble SDK 1.x.
 ** Clone this project on your computer

      git clone isstracker
      cd isstracker/isswatchface

 ** Create the symlinks to the SDK

      ~/pebble-dev/PebbleSDK-1.12/Pebble/tools/create_pebble_project.py --update-symlink ~/pebble-dev/PebbleSDK-1.12/Pebble/ .
      ./waf configure
      ./waf build

 ** Use Dropbox or `python -m SimpleHttpServer` to transfer `build/isswatchface.pbw` to your phone and install it on your Pebble.

## Connectivity

To get the http part working, you will need to install httpebble on your iOS or Android phone:

 - https://play.google.com/store/apps/details?id=com.lukekorth.httpebble&hl=en
 - https://itunes.apple.com/us/app/httpebble/id650174711?mt=8

## Running the server

You will node a working nodejs installation. Anything above 0.10.x should work fine.

    $ npm install
    $ node server.js


