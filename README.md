# ue4_object_pooling
My implementation of object pooling for Unreal Engine 4.

It consists of a spawner that can be placed in a scene and a object pooling component attached to it. I also created a SpawnableActor class which can be inherited in order to use spawner with different actors. 

Following settings can be customized:
 *pool size
 *object's lifespan
 *cooldown between each spawns
 *particle mode (spawned objects are moving outwards from spawner)
 *particles velocity

demo:
