#version 330 core
in vec2 UV;
in vec3 lightDir;

out vec4 FragColor;

uniform sampler2D shadowMap;
uniform sampler2D albedo;

vec2 GetSampleOffsetY(vec2 coord, float yOffset)
{
	const float sixth = 1.0f / 6;

	float yOffsetNormalized = yOffset * sixth;

	vec2 output = coord + vec2(0, yOffsetNormalized);

	//If inside, we are done

	if (trunc(output.y * 6) == trunc(coord.y * 6) && output.y > 0) return output;

	//PositiveX
	if (coord.y < sixth)
	{
		//going down
		if (yOffset > 0)
		{
			//straight up to slice 5
			return coord + vec2(0, (yOffset + 4) * sixth);
		}
		else //flip x, then go down in slice 4 (aka top view)
		{
			return vec2(1-coord.x, -(coord.y + yOffsetNormalized)  + 4 * sixth);
		}
	}
	else if (coord.y < 2 * sixth) //Negative X
	{
		//going down
		if (yOffset > 0)
		{

			return vec2(1 - coord.x, 8 * sixth - output.y);
		}
		else
		{
			return vec2(coord.x, output.y + 4*sixth);
		}
	}
	else if (coord.y < 3 * sixth) //Positive y
	{
		//going down
		if (yOffset > 0)
		{

			return vec2((output.y - 3*sixth)*6, (6-coord.x) * sixth);
		}
		else
		{
			return vec2(1-(2 * sixth-output.y)*6, (5 - coord.x) * sixth);
		}
	}
	else if (coord.y < 4 * sixth) //negative y
	{
		//going down
		if (yOffset > 0)
		{

			return vec2(1 - (output.y - 4 * sixth) * 6, (5 + coord.x) * sixth);
		}
		else
		{
			return vec2(3*sixth - output.y, (coord.x+4)*sixth);
		}
	}
	else if (coord.y < 5 * sixth) //Positive z
	{
		//going down
		if (yOffset > 0)
		{

			return vec2(coord.x, output.y-4*sixth);
		}
		else
		{
			return vec2(1 - coord.x, -(output.y - 4 * sixth));
		}
	}
	else
	{
		//going down
		if (yOffset > 0)
		{

			return vec2(1 - coord.x, 8 * sixth-(output.y));
		}
		else
		{
			return vec2(coord.x, (output.y - 4 * sixth));
		}
	}

	return coord;
}

// Our sampler for the texture, which is just going to be pretty simple
vec2 GetSampleOffsetX(vec2 coord, float xOffset)
{
	vec2 output = coord + vec2(xOffset, 0);

	//If inside, we are done
	if (output.x == clamp(output.x, 0.0, 1.0)) return output;

	// a possible precision problem?
	const float sixth = 1.0f / 6;

	float overlap = output.x - clamp(output.x, 0.0, 1.0);

	//Otherwise we need to traverse to other projections/slides
	if (output.y < sixth)
	{
		//Positive X
		//Go to the right
		if (overlap > 0)
		{
			return vec2(overlap, coord.y + 3 * sixth);
		}
		else
		{
			return vec2(1 + overlap, coord.y + 2 * sixth);
		}
	}
	else if (output.y < 2 * sixth)
	{
		//Negative X
		if (overlap > 0)
		{
			return vec2(overlap, coord.y + sixth);
		}
		else
		{
			return vec2(1 + overlap, coord.y + 2 * sixth);
		}
	}
	else if (output.y < 3 * sixth)
	{
		//Positive Y
		//Go to the right
		if (overlap > 0)
		{
			return vec2(overlap, coord.y - 2 * sixth); //pos->
		}
		else
		{
			return vec2(1 + overlap, coord.y - sixth);
		}
	}
	else if (output.y < 4 * sixth)
	{
		//Negative Y
		//Go to the right
		if (overlap > 0)
		{
			return vec2(overlap, coord.y - 2 * sixth);
		}
		else
		{
			return vec2(1 + overlap, coord.y - 3 * sixth);
		}
	}
	else if (output.y < 5 * sixth)
	{
		//Positive Z
		if (overlap > 0) //Goes into Positive Y
		{
			vec2 flip = vec2((coord.y - 4 * sixth) * 6, (overlap + 2) * sixth);
			flip.x = 1 - flip.x;
			return flip;
		}
		else
		{
			vec2 flip = vec2((coord.y - 4 * sixth) * 6, (-overlap + 3) * sixth);
			//flip.x = 1 - flip.x;
			return flip;
		}
	}
	else
	{
		if (overlap > 0) //Goes into Positive Y
		{
			vec2 flip = vec2((coord.y - 5 * sixth) * 6, (-overlap + 4) * sixth);
			/*flip.x = 1 - flip.x;*/
			return flip;
		}
		else
		{
			vec2 flip = vec2((coord.y - 5 * sixth) * 6, (overlap + 3) * sixth);
			flip.x = 1 - flip.x;
			return flip;
		}
	}

	return coord;
}

//Translates from world space vector to a coordinate inside our 6xsize shadow map
vec2 GetSampleCoordinate(vec3 original)
{
	vec2 coord;
	float slice;

	float absX = abs(original.x);
	float absY = abs(original.y);
	float absZ = abs(original.z);

	if (absX >= absY && absX >= absZ)
	{
		if (original.x > 0) //Positive X
		{
			slice = 0;
			original /= absX;
			coord.x = -original.z;
			coord.y = -original.y;
		}
		else
		{
			slice = 1; //Negative X

			original /= abs(original.x);
			coord.x = original.z;
			coord.y = -original.y;
		}
	}
	else if (absY >= absX && absY >= absZ)
	{
		if (original.y > 0)
		{
			slice = 2; // PositiveY;
			original /= absY;
			coord.x = original.x;
			coord.y = original.z;
		}
		else
		{
			slice = 3; // NegativeY;
			original /= absY;
			coord.x = original.x;
			coord.y = -original.z;
		}
	}
	else
	{
		//Z
		if (original.z > 0) //Pos Z
		{
			slice = 4;
			original /= absZ;
			coord.x = original.x;
			coord.y = -original.y;
		}
		else
		{
			slice = 5; // NegativeZ;
			original /= absZ;
			coord.x = -original.x;
			coord.y = -original.y;
		}
	}


	// a possible precision problem?
	const float sixth = 1.0f / 6;

	//now we are in [-1,1]x[-1,1] space, so transform to texCoords
	coord = (coord + vec2(1, 1)) * 0.5f;

	//now transform to slice position
	coord.y = coord.y * sixth + slice * sixth;
	return coord;
}
vec2 GetSampleOffset(vec2 coord, vec2 offset)
{
	coord = GetSampleOffsetX(coord, offset.x);
	coord = GetSampleOffsetY(coord, offset.y);

	return coord;
}

float random(vec4 seed)
{
   float dot_product = dot(seed, vec4(12.9898,78.233,45.164,94.673));
   return fract(sin(dot_product) * 43758.5453);
}

void main()
{
    float currentDist = length(lightDir);

    float fShadowTerm = 0.0;


    FragColor = vec4(texture(albedo, UV).rgb,1.0) * visibility;
}




    // Apply slope scale bias
    //float ddistdx = dFdx(sampledDist);
    //float ddistdy = dFdy(sampledDist);
    //sampledDist += slopeBias * abs(ddistdx);
    //sampledDist += slopeBias * abs(ddistdy);

    //float fShadow = (currentDist  - sampledDist - 0.65< 0.0) ? 1.0 : 0.0;