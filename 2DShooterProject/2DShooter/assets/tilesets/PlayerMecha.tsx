<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Player" tilewidth="64" tileheight="64" spacing="2" margin="2" tilecount="27" columns="3">
 <image source="../images/PlayerMecha.png" width="200" height="596"/>
 <tile id="0" type="mechaIdle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="14" y="9" width="20" height="35"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="50"/>
   <frame tileid="2" duration="50"/>
   <frame tileid="1" duration="50"/>
  </animation>
 </tile>
 <tile id="2" type="idleBack">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="19" y="9" width="20" height="35"/>
  </objectgroup>
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
 <tile id="6" type="mechaAttack">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="14" y="7" width="20" height="41.9545"/>
   <object id="2" name="firingPoint" type="PlayerBullet" x="64.1818" y="13.0909">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="6" duration="50"/>
   <frame tileid="8" duration="50"/>
   <frame tileid="7" duration="50"/>
  </animation>
 </tile>
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
 <tile id="15" type="ship">
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
   <frame tileid="16" duration="100"/>
   <frame tileid="17" duration="100"/>
  </animation>
 </tile>
 <tile id="18" type="shipMoveAnim">
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
   <frame tileid="18" duration="200"/>
   <frame tileid="19" duration="100"/>
   <frame tileid="20" duration="100"/>
  </animation>
 </tile>
 <tile id="24" type="mechaAttackAnim">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="12.3636" y="9.02275" width="20" height="41.9545"/>
   <object id="2" name="firingPoint" type="PlayerBullet" x="65.6364" y="18.7273">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="24" duration="50"/>
   <frame tileid="26" duration="50"/>
   <frame tileid="25" duration="50"/>
  </animation>
 </tile>
</tileset>
