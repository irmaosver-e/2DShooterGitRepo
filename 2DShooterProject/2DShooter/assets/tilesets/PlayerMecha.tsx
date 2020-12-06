<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Player" tilewidth="64" tileheight="64" spacing="2" margin="2" tilecount="30" columns="6">
 <image source="../images/PlayerMecha.png" width="398" height="332"/>
 <tile id="0" type="mechaIdle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="14" y="9" width="20" height="35"/>
  </objectgroup>
  <animation>
   <frame tileid="2" duration="50"/>
   <frame tileid="0" duration="50"/>
   <frame tileid="1" duration="50"/>
  </animation>
 </tile>
 <tile id="3" type="mechaAttackAnim"/>
 <tile id="6" type="mechaAttackTransition">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="15.8182" y="10.6818" width="20" height="35"/>
  </objectgroup>
  <animation>
   <frame tileid="8" duration="50"/>
   <frame tileid="6" duration="50"/>
   <frame tileid="7" duration="50"/>
  </animation>
 </tile>
 <tile id="9" type="morph"/>
 <tile id="12" type="mechaAttack">
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
   <frame tileid="14" duration="50"/>
   <frame tileid="12" duration="50"/>
   <frame tileid="13" duration="50"/>
  </animation>
 </tile>
 <tile id="15" type="ship"/>
 <tile id="18" type="transform">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="11.8182" y="25.75" width="23.4545" height="20.6818"/>
  </objectgroup>
  <animation>
   <frame tileid="18" duration="50"/>
   <frame tileid="19" duration="50"/>
   <frame tileid="20" duration="50"/>
   <frame tileid="24" duration="50"/>
   <frame tileid="25" duration="50"/>
   <frame tileid="26" duration="50"/>
  </animation>
 </tile>
 <tile id="26" type="ship">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="firingPoint" type="PlayerBullet" x="62.75" y="44.75">
    <point/>
   </object>
   <object id="2" name="collisionBox" x="5.5" y="33.2728" width="32.25" height="19.2045"/>
  </objectgroup>
  <animation>
   <frame tileid="24" duration="50"/>
   <frame tileid="25" duration="50"/>
   <frame tileid="26" duration="50"/>
   <frame tileid="27" duration="50"/>
   <frame tileid="28" duration="50"/>
  </animation>
 </tile>
</tileset>
