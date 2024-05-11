using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UIMap : UIPopup
{
    [SerializeField] private Transform parent;
    [SerializeField] private TMP_Dropdown dropDown;
    [SerializeField] private Button exitButton;

    private List<UIPlace> places = new List<UIPlace>();

    private void Start()
    {
        List<string> options = new List<string>();
        foreach(PlaceSO place in GameManager.Map.CurMap.Places)
        {
            if(place.PlacePrefab == null)
            {
                continue;
            }
            GameObject placePrefab = Instantiate(place.PlacePrefab, parent);
            placePrefab.transform.SetAsFirstSibling();
            placePrefab.SetActive(false);
            places.Add(placePrefab.GetComponent<UIPlace>());
            options.Add(place.Name);
        }

        dropDown.AddOptions(options);
        
        UpdateMap(0);
        dropDown.onValueChanged.AddListener(UpdateMap);
        exitButton.onClick.AddListener(ClosePopup);

        foreach (UIPlace placePrefab in places)
        {
            placePrefab.DeActivateSpots();
        }

        foreach (int id in GameManager.Map.curActivatedSpot)
        {
            foreach (UIPlace placePrefab in places)
            {
                placePrefab.ActivateSpotButton(id);
            }
        }
    }

    private void UpdateMap(int idx)
    {
        foreach(UIPlace place in places)
        {
            place.gameObject.SetActive(false);
        }

        if(places[idx] != null)
        {
            places[idx].gameObject.SetActive(true);
        }
    }

    private void ClosePopup()
    {
        GameManager.UI.ClosePopupUI(this);
    }

    public UISpot GetSpotToId(int Id)
    {
        foreach (UIPlace placePrefab in places)
        {
            UISpot spot = placePrefab.GetUISpot(Id);
            if (spot != null)
            {
                return spot;
            }
        }
        return null;
    }
}
