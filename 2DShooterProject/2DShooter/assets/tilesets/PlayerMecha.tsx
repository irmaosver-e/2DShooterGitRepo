<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Player" tilewidth="64" tileheight="64" spacing="2" margin="2" tilecount="42" columns="6">
 <image source="../images/PlayerMecha.png" width="398" height="464"/>
 <tile id="0" type="mechaIdle">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="14" y="9" width="20" height="35"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="50"/>
   <frame tileid="1" duration="50"/>
   <frame tileid="2" duration="50"/>
   <frame tileid="3" duration="50"/>
   <frame tileid="4" duration="50"/>
  </animation>
 </tile>
 <tile id="2" type="lifeCounter">
  <animation>
   <frame tileid="2" duration="200"/>
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
   <frame tileid="6" duration="50"/>
   <frame tileid="7" duration="50"/>
   <frame tileid="8" duration="50"/>
   <frame tileid="9" duration="50"/>
   <frame tileid="10" duration="50"/>
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
   <frame tileid="12" duration="50"/>
   <frame tileid="13" duration="50"/>
   <frame tileid="14" duration="50"/>
   <frame tileid="15" duration="50"/>
   <frame tileid="16" duration="50"/>
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
   <frame tileid="21" duration="50"/>
   <frame tileid="22" duration="50"/>
   <frame tileid="23" duration="50"/>
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
 <tile id="30" type="playerExplosion">
  <properties>
   <property name="OwnerSubType" value="playermecha"/>
  </properties>
  <animation>
   <frame tileid="30" duration="50"/>
   <frame tileid="31" duration="50"/>
   <frame tileid="32" duration="50"/>
   <frame tileid="33" duration="50"/>
   <frame tileid="34" duration="50"/>
   <frame tileid="36" duration="50"/>
   <frame tileid="37" duration="50"/>
   <frame tileid="38" duration="50"/>
   <frame tileid="39" duration="50"/>
  </animation>
 </tile>
</tileset>
