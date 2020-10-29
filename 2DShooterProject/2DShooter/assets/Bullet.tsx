<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Bullet" tilewidth="32" tileheight="32" spacing="2" margin="2" tilecount="2" columns="2">
 <image source="bullet.png" width="70" height="36"/>
 <tile id="0" type="yellow">
  <properties>
   <property name="OwnerSubType" value="bulletPlayer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="9.75" y="9.97727" width="11.1818" height="11.0909"/>
   <object id="2" name="anchor" type="PlayerBullet" x="15.5" y="15.5">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="400"/>
  </animation>
 </tile>
 <tile id="1" type="pink">
  <properties>
   <property name="OwnerSubType" value="bulletEnemy"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="9.6591" y="10.2046" width="11.1818" height="11.0909"/>
   <object id="2" name="anchor" type="EnemyBullet" x="15.5" y="15.5">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="1" duration="400"/>
  </animation>
 </tile>
</tileset>
