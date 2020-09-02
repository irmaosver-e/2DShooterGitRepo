<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.3.5" name="MenuButton" tilewidth="192" tileheight="64" spacing="2" margin="2" tilecount="4" columns="2">
 <image source="../../../../../../testAssets/MenuButtons.png" width="390" height="134"/>
 <tile id="0" type="playbutton">
  <properties>
   <property name="VsCollision" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="colisionBox" x="12" y="12" width="168" height="40"/>
  </objectgroup>
  <animation>
   <frame tileid="2" duration="400"/>
   <frame tileid="0" duration="400"/>
  </animation>
 </tile>
 <tile id="1" type="exitbutton">
  <properties>
   <property name="VsCollision" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="colisionBox" x="12" y="12" width="168" height="40"/>
  </objectgroup>
  <animation>
   <frame tileid="3" duration="400"/>
   <frame tileid="1" duration="400"/>
  </animation>
 </tile>
</tileset>
