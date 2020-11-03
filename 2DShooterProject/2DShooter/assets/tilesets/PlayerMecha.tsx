<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Player" tilewidth="64" tileheight="64" spacing="2" margin="2" tilecount="9" columns="3">
 <image source="../images/PlayerMecha.png" width="202" height="202"/>
 <tile id="0" type="idle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="14" y="9" width="20" height="35"/>
  </objectgroup>
  <animation>
   <frame tileid="2" duration="400"/>
   <frame tileid="0" duration="400"/>
   <frame tileid="1" duration="400"/>
  </animation>
 </tile>
 <tile id="1" type="idleForward"/>
 <tile id="2" type="idleBack">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <animation>
   <frame tileid="2" duration="400"/>
  </animation>
 </tile>
 <tile id="3" type="damageIdle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="15.8182" y="10.6818" width="20" height="35"/>
  </objectgroup>
  <animation>
   <frame tileid="5" duration="400"/>
   <frame tileid="3" duration="400"/>
   <frame tileid="4" duration="400"/>
  </animation>
 </tile>
 <tile id="4" type="damageForward"/>
 <tile id="5" type="damageBack"/>
 <tile id="6" type="attackIdle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="14" y="7" width="20" height="41.9545"/>
   <object id="2" name="firingPoint" type="PlayerBullet" x="64.1818" y="17.0909">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="8" duration="400"/>
   <frame tileid="6" duration="400"/>
   <frame tileid="7" duration="400"/>
  </animation>
 </tile>
 <tile id="7" type="attackForward"/>
 <tile id="8" type="attackBack"/>
</tileset>
