using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIHeartRateGraph : MonoBehaviour
{
    [SerializeField] private Image viewport;
    [SerializeField] private GameObject graphPrefab;
    [SerializeField] private float graphSpeed = 130.0f;

    [SerializeField] private List<Sprite> graphBpm80;
    [SerializeField] private List<Sprite> graphBpm90;
    [SerializeField] private List<Sprite> graphBpm100;
    [SerializeField] private List<Sprite> graphBpm110;
    [SerializeField] private List<Sprite> graphBpm120;
    [SerializeField] private List<Sprite> graphBpm130;

    [SerializeField] private List<Sprite> curGraphSprite;

    private GameObject prevGraph = null;

    private void OnEnable()
    {
        StartCoroutine(SpawnGraph());
    }

    private void OnDisable()
    {
        StopCoroutine(SpawnGraph());
    }

    private IEnumerator SpawnGraph()
    {
        while (true)
        {
            if (CanSpawnGraph())
            {
                ChangeGraphForHeartRate(GameManager.HeartRate.CurHeartRate);
                GameObject graph = Instantiate(graphPrefab, viewport.transform);
                DrawRandomGraph(curGraphSprite);
                graph.transform.localPosition = new Vector3(graph.GetComponent<RectTransform>().rect.width / 2 + viewport.rectTransform.rect.width / 2, 0, 0);
                StartCoroutine(UpdateGraph(graph));
                prevGraph = graph;
            }
            yield return null;
        }
    }

    private IEnumerator UpdateGraph(GameObject graph)
    {
        RectTransform graphRect = graph.GetComponent<RectTransform>();

        while (graphRect.localPosition.x + graphRect.rect.width / 2 > -viewport.rectTransform.rect.width / 2)
        {
            graphRect.localPosition -= new Vector3(graphSpeed * Time.deltaTime, 0, 0);
            yield return null;
        }

        Destroy(graph);
    }

    private bool CanSpawnGraph()
    {
        if (prevGraph == null)
        {
            return true;
        }

        RectTransform graphRect = prevGraph.GetComponent<RectTransform>();
        RectTransform viewportRect = viewport.rectTransform;

        float viewportRightEdge = viewportRect.rect.width / 2;
        float graphRightEdge = graphRect.localPosition.x + graphRect.rect.width / 2;

        return graphRightEdge < viewportRightEdge;
    }

    private void ChangeGraphForHeartRate(float heartRate)
    {
        if (heartRate < 90.0f)
        {
            curGraphSprite = graphBpm80;
            graphSpeed = 130.0f;
        }
        else if (heartRate >= 90.0f && heartRate < 100.0f)
        {
            curGraphSprite = graphBpm90;
            graphSpeed = 140.0f;
        }
        else if (heartRate >= 100.0f && heartRate < 110.0f)
        {
            curGraphSprite = graphBpm100;
            graphSpeed = 150.0f;
        }
        else if (heartRate >= 110.0f && heartRate < 120.0f)
        {
            curGraphSprite = graphBpm110;
            graphSpeed = 160.0f;
        }
        else if (heartRate >= 120.0f && heartRate < 130.0f)
        {
            curGraphSprite = graphBpm120;
            graphSpeed = 170.0f;
        }
        else if (heartRate >= 130.0f && heartRate < 140.0f)
        {
            curGraphSprite = graphBpm130;
            graphSpeed = 180.0f;
        }
    }

    private void DrawRandomGraph(List<Sprite> graphs)
    {
        int idx = Random.Range(0, graphs.Count);

        Image graphImage = graphPrefab.GetComponent<Image>();
        graphImage.sprite = graphs[idx];
    }
}
