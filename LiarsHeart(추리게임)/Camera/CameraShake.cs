using System.Collections;
using UnityEngine;

public class CameraShake
{
    private Camera camera;
    public Coroutine curCoroutine = default;

    public CameraShake(Camera camera)
    {
        this.camera = camera;
    }

    public void Play(MonoBehaviour monoBehaviour, float shakePower, float shakeDuration)
    {
        if (curCoroutine != null)
        {
            return;
        }

        curCoroutine = monoBehaviour.StartCoroutine(UpdateCamera(shakePower, shakeDuration));
    }

    private IEnumerator UpdateCamera(float shakePower, float shakeDuration)
    {
        Vector3 prePosition = camera.gameObject.transform.position;

        float elapsed = 0.0f;

        while (elapsed < shakeDuration)
        {
            float x = prePosition.x + Random.Range(-1f, 1f) * shakePower;
            float y = prePosition.y + Random.Range(-1f, 1f) * shakePower;

            camera.transform.position = new Vector3(x, y, prePosition.z);

            elapsed += Time.deltaTime;

            yield return null;
        }

        camera.transform.position = prePosition;

        End();
    }

    private void End()
    {
        curCoroutine = null;
    }

    public IEnumerator UpdateEditor(float shakePower, float shakeDuration)
    {
        yield return UpdateCamera(shakePower, shakeDuration);
    }
}
