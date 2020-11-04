<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="Boss1" tilewidth="192" tileheight="256" spacing="2" margin="2" tilecount="1" columns="1">
 <image source="../images/boss1.png" width="196" height="260"/>
 <tile id="0" type="bossIdle">
  <properties>
   <property name="OwnerSubType" value="bossPlane"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="27.1162" y="106.133" width="146.093" height="41.9545"/>
   <object id="2" name="collisionBox" x="12.3714" y="22.2402" width="138.975" height="41.9545"/>
   <object id="3" name="collisionBox" x="11.863" y="191.043" width="140.5" height="41.9545"/>
   <object id="4" name="firingPoint" type="EnemyBullet" x="18.8123" y="130.161">
    <point/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="400"/>
  </animation>
 </tile>
</tileset>
