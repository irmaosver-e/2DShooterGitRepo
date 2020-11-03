<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Cursor" tilewidth="32" tileheight="32" spacing="2" margin="2" tilecount="6" columns="6">
 <image source="../images/Cursors.png" width="206" height="36"/>
 <tile id="0" type="arrow">
  <properties>
   <property name="OwnerSubType" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="3">
   <object id="2" name="collisionBox" x="6" y="1" width="8" height="15"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="150"/>
   <frame tileid="1" duration="150"/>
   <frame tileid="2" duration="150"/>
   <frame tileid="3" duration="150"/>
   <frame tileid="4" duration="150"/>
   <frame tileid="5" duration="150"/>
  </animation>
 </tile>
</tileset>
