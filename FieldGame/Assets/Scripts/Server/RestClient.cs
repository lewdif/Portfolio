using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using SimpleJSON;

class RestClient : Singleton<RestClient>
{
    internal const string PortalURL = "http://localhost:8080/";

    private Dictionary<string, string> session = new Dictionary<string, string>();

    private static string cookie = null;

    public delegate void Callback(JSONNode response);

    public void Request(string request, string method, Callback callback, Dictionary<string, string> input = null)
    {
        Debug.Log("REST Request: url = " + PortalURL + request);

        WWWForm form = null;
        if (input != null)
        {
            form = new WWWForm();
            foreach (var key in input.Keys) 
            {
                print("REST Request: input {" + key + " => " + input[key] + "}");
                form.AddField(key, input[key]);
            }
        }

        WWW www = new WWW(  PortalURL + request, 
                            form != null ? form.data: null, 
                            cookie != null ? new Dictionary<string, string>() { { "Cookie", cookie} } : null );
        StartCoroutine(Process(www, callback));
    }

    public void ClearSession()
    {
        cookie = null;
    }

    private IEnumerator Process(WWW www, Callback callback)
    {
        yield return www;

        if (www.error != null) yield break;
        
        if (cookie == null) // please check whether it contains a session information
        {
            if (www.responseHeaders.ContainsKey("SET-COOKIE"))
            {
                char[] splitter = { ';' };
                string[] v = www.responseHeaders["SET-COOKIE"].Split(splitter);
                foreach (string s in v)
                {
                    if (string.IsNullOrEmpty(s)) continue;
                    Debug.Log("session started : " + s);
                    cookie = s;
                    break;
                }
            }
        }
        
        Debug.Log("REST Response: " + www.text);
        callback(JSON.Parse(www.text));
    }
}