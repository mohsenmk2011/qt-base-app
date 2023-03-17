## List of branches
1. master :the base application of all other branches
2. rokhshid : a beuty app,for being young by face muscles exercises
3. bimeh : users can get tamin insurance sheet and pay it with this app
4. nabat: fale hafez,and reimplemented ganjoor ,  not created yet
5. gira: jooya leitner app,study with no,not created yet
6. hokm: hokm game, not created yet
7. appsaz: the application that will create your application with QmlLive
---
## How change the build directory
1. In qt creator from sidebar click "Projects"
2. from Kits in left pane ,select one and click on "Build",now you can see Build Settings in right pane
3. in Build directory you can see a path like => /home/mohsen/QtProjects/builds/build-jooyaqtapp-android-release , this path is for master branch ,jooyaqtapp is for master branch
4. when you select each branch,you should change the build directory ,so in above path change **jooyaqtapp** to **rokhshid**,**bimeh**,**gira** or ...
---
## Steps to do after creating new branch from master branch
    1. change package name of application:first open AndroidManifest file and then change package,application,activty and version name and version code
    2. rename src folder name:after renaming PWD/android/src/org/jooya/jooyaqtapp => PWD/android/src/org/jooya/yourapplicationname
    3. rename all path of using src folder:
        - first search for **jooyaqtapplication**  
        - then replace it with your app name
        - for example 'package org.jooya.jooyaqtapplication' will changed to 'package org.jooya.rokhshid'
        - for example 'QAndroidJniObject javaClass("org/jooya/jooyaqtapplication/SmsManager")' will changed to 'QAndroidJniObject javaClass("org/jooya/rokhshid/SmsManager").
    4. download icon in png format 512px or higher
    5. convert it to *.ico
    6. Change the Application icon: open AndroidManifest.xml file then go to Advanced -> Application icon -> Master icon and select your new application icon file(png file)
    7. do this for SplashScreen too
    8. replace new icon.ico and icon.png with old ones
    9. rename application pro files(ex:jooyabaseqtapp --rename--> rokhshid).
    10. rename AppSettings and AppPath classes
    11. change application names and urls:
        - Serach for "TODO: Change this after creating new branch from master branch" and change all of them.
---
## How preview *.md file in visual studio code
* press Ctrl+K V for preview side by side (and real time)
* press Ctrl+Shift+V preview in new tab
---


