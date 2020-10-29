<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Player" tilewidth="64" tileheight="64" spacing="2" margin="2" tilecount="6" columns="3">
 <image source="PlayerMecha.png" width="202" height="136"/>
 <tile id="0" type="idle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="14" y="9" width="20" height="35"/>
   <object id="2" name="firingPoint" type="PlayerBullet" x="63.125" y="13.5">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="300"/>
   <frame tileid="1" duration="300"/>
   <frame tileid="2" duration="300"/>
   <frame tileid="3" duration="300"/>
   <frame tileid="4" duration="300"/>
   <frame tileid="5" duration="300"/>
  </animation>
 </tile>
 <tile id="2" type="lives">
  <animation>
   <frame tileid="2" duration="400"/>
  </animation>
 </tile>
 <tile id="5" type="legs">
  <animation>
   <frame tileid="5" duration="400"/>
  </animation>
 </tile>
</tileset>
