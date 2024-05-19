using System.Collections.Generic;
using UnityEngine;

public class UIPlace : MonoBehaviour
{
    [SerializeField] private List<UISpot> Spots = new List<UISpot>();

    public void DeActivateSpots()
    {
        foreach (UISpot spot in Spots)
        {
            spot.gameObject.SetActive(false);
        }
    }
    public UISpot GetUISpot(int id)
    {
        foreach(UISpot spot in Spots)
        {
            if(spot.GetSpotId() == id)
            {
                return spot;
            }
        }
        return null;
    }

    public void ActivateSpotButton(int id)
    {
        foreach (UISpot spot in Spots)
        {
            if (spot.GetSpotId() == id)
            {
                spot.gameObject.SetActive(true);
            }
        }
    }
}
