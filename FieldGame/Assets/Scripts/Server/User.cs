using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using SimpleJSON;

class User : Singleton<User>
{
    string user_id = null;
    RestClient rest_client = null;

    void Awake()
    {
        rest_client = gameObject.AddComponent<RestClient>();
    }

    void ResLogin(JSONNode result)
    {
        var error = result["result"]["error"];
        if (error.Value == "no")
        {
            if (result["name"] != null)
            {
                print(result["name"].Value);
            }
#if PLEASE_ASSOCIATE_UNIQUE_ID_WITH_REGISTERED_USERID_FIRST
                PlayerPrefs.SetString("User Identifier", user_id);
                PlayerPrefs.SetString("Saved Password", PlayerPrefs.GetString("Saved Password"));
                PlayerPrefs.Save();
#endif
        }
    }

    public void ReqLogin(Dictionary<string, string> input = null, RestClient.Callback callback = null)
    {
        rest_client.Request("login.php", "post", callback == null ? ResLogin : callback, input);
    }

    public void ReqLogout()
    {
        rest_client.Request("logout.php", "post", (result) =>
        {
            var error = result["error"];
            if (error.Value == "no")
                rest_client.ClearSession();
        });
    }

    public void ReqRegister(Dictionary<string, string> input = null)
    {
        print(input.ToString());
        rest_client.Request("register.php", "post", (result) =>
        {
            var error = result["error"];
            if (error.Value == "no")
            {
                // redirect to login automatically.
                ReqLogin(new Dictionary<string, string>() { { "userid", input["userid"] }, { "password", input["passwd"] } });   
            }
        }, input);
    }

    public void ReqUnregister()
    {
        rest_client.Request("unregister.php", "post", (result) =>
        {
            var error = result["error"];
            if (error.Value == "no")
                rest_client.ClearSession();
        });
    }
}