<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Player" tilewidth="64" tileheight="64" spacing="2" margin="2" tilecount="24" columns="3">
 <image source="../images/PlayerMecha.png" width="200" height="530"/>
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
 <tile id="9" type="morph">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="11.8182" y="25.75" width="23.4545" height="20.6818"/>
  </objectgroup>
  <animation>
   <frame tileid="9" duration="100"/>
   <frame tileid="10" duration="100"/>
   <frame tileid="11" duration="100"/>
   <frame tileid="12" duration="100"/>
   <frame tileid="13" duration="100"/>
   <frame tileid="14" duration="100"/>
  </animation>
 </tile>
 <tile id="15" type="shipIdle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="6" y="35.1" width="39.1" height="9.8"/>
   <object id="2" name="collisionBox" x="6.90455" y="24.1" width="8.5" height="9.8"/>
   <object id="3" name="firingPoint" type="PlayerBullet" x="61.4545" y="44.7273">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="15" duration="200"/>
  </animation>
 </tile>
 <tile id="18" type="shipUp">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="5" y="32.4" width="31.3" height="16.7"/>
   <object id="2" name="firingPoint" type="PlayerBullet" x="62.3636" y="44.5455">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="18" duration="100"/>
   <frame tileid="19" duration="100"/>
  </animation>
 </tile>
 <tile id="21" type="shipDown">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="5" y="32.4" width="31.3" height="16.7"/>
   <object id="2" name="firingPoint" type="PlayerBullet" x="62" y="44.5455">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="21" duration="100"/>
   <frame tileid="22" duration="100"/>
  </animation>
 </tile>
</tileset>
