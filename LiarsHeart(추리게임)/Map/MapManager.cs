using System.Collections.Generic;

public class MapManager
{
    private MapSO curMap;
    public MapSO CurMap { get => curMap; }

    public List<int> curActivatedSpot = new List<int>();
    private UIMap mapUI;

    public void SetMapData(MapSO mapSO)
    {
        curMap = mapSO;

        //∏  πŸ≤Ó∏È √ ±‚»≠
        curActivatedSpot.Clear();
        curActivatedSpot.Add(1);
    }

    public void SetMapUI(UIPopup popup)
    {
        mapUI = popup as UIMap;
    }

    public UIMap GetMapUI()
    {
        if(mapUI != null)
        {
            return mapUI;
        }
        return null;
    }

    public UISpot GetSpotToId(int id)
    {
        if(mapUI == null)
        { 
            return null;
        }

        UISpot spot = mapUI.GetSpotToId(id);
        if(spot != null)
        {
            return spot;
        }

        return null;
    }
}
