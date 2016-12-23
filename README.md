# ue4_object_pooling
My implementation of object pooling for Unreal Engine 4.

It consists of a spawner that can be placed in a scene and a object pooling component attached to it. Spawner uses a PoolableActor class which can be inherited by actors that require pooling. 

Following settings can be customized:
 *pool size
 *object's lifespan
 *cooldown between each spawns
 *particle mode (spawned objects are moving outwards from spawner)
 *particles velocity

demo:
