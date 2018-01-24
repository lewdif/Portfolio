using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{
    private AudioSource attackSound;
    public AudioClip slurp;

    private float monsSpeed;
    private int monsHP;
    private Transform target;
    private float monsStep;
    private GameObject player;
    private bool isCol;

    public GameObject Heart;
    private int randNum;
    
    private Animation animation;

    void Start ()
    {
        attackSound = this.gameObject.AddComponent<AudioSource>();
        attackSound.clip = slurp;
        attackSound.loop = false;

        player = GameObject.Find("Player");
        monsHP = 10;
        monsSpeed = 2.0f;
        target = player.transform;
        monsStep = monsSpeed * Time.deltaTime;

        isCol = false;

        randNum = Random.Range(0, 11);

        animation = GetComponentInChildren<Animation>();

        StartCoroutine(slimeControl());
    }

    void Update()
    {

    }
    
    void OnTriggerEnter(Collider target)
    {
        if (target.gameObject.tag.Equals("Bullet"))
        {
            if (randNum % 3 == 0)
            {
                GameObject go = GameObject.Instantiate(Heart) as GameObject;
                go.transform.position = new Vector3(transform.position.x, transform.position.y + 0.5f, transform.position.z);
            }
            Destroy(gameObject);
        }
    }

    private IEnumerator slimeControl()
    {
        while (true)
        {
            transform.LookAt(new Vector3(target.position.x, 0, target.position.z));

            if (Vector3.Distance(transform.position, new Vector3(target.position.x, 0, target.position.z)) < 2.0f)
            {
                StartCoroutine(slimeAttack());
                yield return new WaitForSeconds(2.0f);
            }
            else
            {
                animation.Play("Walk");
                transform.position = Vector3.MoveTowards(transform.position, new Vector3(target.position.x, 0, target.position.z), monsStep);
            }
            yield return null;
        }
    }

    private IEnumerator slimeAttack()
    {
        attackSound.Play();
        player.GetComponent<PlayerControl>().Damaged();
        animation.Play("Attack");
        yield return new WaitForSeconds(2.0f);
    }
}