using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyFence : MonoBehaviour
{
    private GameObject player;
    private bool isPushed;

    void Start()
    {
        isPushed = false;
        player = GameObject.Find("Player");
    }

    void Update()
    {
        /*if(isPushed && Input.GetKeyDown(KeyCode.V))
        {
            player.GetComponent<PlayerControl>().GetWoodFromFence();
            Destroy(this.gameObject);
        }*/
        /*if (Input.GetKey(KeyCode.V))
        {
            isPushed = true;
        }

        if(Input.GetKeyUp(KeyCode.V))
        {
            isPushed = false;
        }*/
    }
    /*
    void OnTriggerEnter(Collider target)
    {
        if (target.gameObject.tag.Equals("Player"))
        {
            if (isPushed == true)
            {
                Debug.Log("!!!!!!");
                player.GetComponent<PlayerControl>().GetWoodFromFence();
                Destroy(gameObject);
            }
        }
    }*/
}
