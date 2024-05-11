using System.Collections;
using UnityEngine;

public class CameraZoom
{
    private Camera camera;
    public Coroutine curCoroutine = default;

    private float leftEnd;
    private float rightEnd;
    private float bottomEnd;
    private float topEnd;

    private float orthographicSize;

    public CameraZoom(Camera camera)
    {
        this.camera = camera;
        InitializeCamera();
    }

    private void InitializeCamera()
    {
        float width = camera.orthographicSize * camera.aspect * 2;
        float height = camera.orthographicSize * 2;

        leftEnd = camera.transform.position.x - (width / 2);
        rightEnd = camera.transform.position.x + (width / 2);
        bottomEnd = camera.transform.position.y - (height / 2);
        topEnd = camera.transform.position.y + (height / 2);

        orthographicSize = camera.orthographicSize;
    }

    public void Play(MonoBehaviour monoBehaviour, Vector3 targetPos, float zoomSize, float zoomSpeed)
    {
        if (curCoroutine != null)
        {
            return;
        }

        curCoroutine = monoBehaviour.StartCoroutine(UpdateCamera(targetPos, zoomSize, zoomSpeed));
    }

    private IEnumerator UpdateCamera(Vector3 targetPos, float zoomSize, float zoomSpeed)
    {
        float progress = 0.0f;
        zoomSize = Mathf.Clamp(zoomSize, 0.0f, orthographicSize);

        while (progress < 1.0f)
        {
            progress += Time.deltaTime * zoomSpeed;

            float xPos = Mathf.Lerp(camera.transform.position.x, targetPos.x, progress);
            float yPos = Mathf.Lerp(camera.transform.position.y, targetPos.y, progress);
            float nextSize = Mathf.Lerp(camera.orthographicSize, zoomSize, progress);

            xPos = Mathf.Clamp(xPos, leftEnd + nextSize * camera.aspect, rightEnd - nextSize * camera.aspect);
            yPos = Mathf.Clamp(yPos, bottomEnd + nextSize, topEnd - nextSize);

            camera.transform.position = new Vector3(xPos, yPos, camera.transform.position.z);
            camera.orthographicSize = nextSize;

            yield return null;
        }

        End();
    }

    private void End()
    {
        curCoroutine = null;
    }

    public IEnumerator UpdateEditor(Vector3 targetPos, float zoomSize, float zoomSpeed)
    {
        yield return UpdateCamera(targetPos, zoomSize, zoomSpeed);
    }
}
