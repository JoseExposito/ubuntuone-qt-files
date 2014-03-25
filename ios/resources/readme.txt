
                                       HOW TO DEPLOY AN IOS VERSION:
                                       —————————————————————————————
[+] SETTING VERSION:

    - Compile the project with Qt Creator
    - Edit the Info.plist file to update the version
    - Replace the Info.plist in the build folder (Xcode project directory)

[+] SETTING ICONS AND LAUNCH IMAGES

    - Open the generated Xcode project
    - Validate project settings if necessary
    - Select the project and in the General tab go down to App Icons section
    - Click for Source “Use Asset Catalog"
    - Copy the “ios/resourcesImages.xcassets” into the “U1Files” folder (Xcode project directory)
    - Remember to disable the gloss on iOS 6
      http://stackoverflow.com/a/18593109/1204395
