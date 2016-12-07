/*
 *   Copyright 2016 The Foundry Visionmongers Ltd.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#pragma once

#include "LevelEditor.h"
#include "XmlParser.h"

#include "Materials/MaterialExpression.h"

#include "ModoMaterialImporterAssignment.h"
#include "ModoMaterialImporterTextureManager.h"

namespace ModoMaterial
{
    
    enum ChannelType {FLOAT_CHANNEL,VECTOR_CHANNEL,COLOR_CHANNEL};
	
    class MaterialCreator
	{
	public:

		static void LoadMaterial(FXmlFile *matXml, const FString &path, Assignment* matAssign);

	private:

		struct ImageInfo
		{
			FString filename;
			ColorSpace colorSpace; 
		};

		struct TextureInfo
		{
			const FXmlNode* node;
			FString filename;
			bool isSRGB; 
		};
        
        template <typename T>
        static bool AddOneMinusParam(FXmlNode * node, UMaterial * material, FMaterialInput<T> * material_input, FExpressionInput * input, int & graphx, int & graphy, ChannelType type);
        template <typename T>
        static bool AddNoiseParam(FXmlNode * node, UMaterial * material, FMaterialInput<T> * material_input, FExpressionInput * input, int & graphx, int & graphy, ChannelType type);
        template <typename T>
        static bool AddLerpParam(FXmlNode * node, UMaterial * material, FMaterialInput<T>* matInput, FExpressionInput * input, int & graphx, int & graphy, ChannelType type);
        template <typename T>
        static bool    AddMultiplyParam(FXmlNode * node, UMaterial * material, FMaterialInput<T>* material_input, FExpressionInput * input, int & graphx, int & graphy, ChannelType type);
        template <typename T> 
        static bool AddCompositeParam( FXmlNode * node, UMaterial * material, FMaterialInput<T>* matInput,  FExpressionInput * input, int & graphx, int & graphy, ChannelType type);

		static void FindTextureNodes(const FXmlNode *Node, TArray<TextureInfo>& txtrInfos);
		static bool AddFloatParam(FXmlNode *Node, UMaterial* mat, FMaterialInput<float>* matInput, FExpressionInput * input, int & graphx, int & graphy);
		static bool AddVectorParam(FXmlNode *Node, UMaterial* mat, FMaterialInput<FVector>* matInput, FExpressionInput * input,int & graphx, int & graphy, EMaterialSamplerType type);
		static bool AddColorParam(FXmlNode *Node, UMaterial* mat, FMaterialInput<FColor>* matInput, FExpressionInput * input, int & graphx, int & graphy, bool maskRGB = false);
		static void AddUnknownParam(FXmlNode *Node, UMaterial* mat, int & graphx, int & graphy);

		static FString _path, _rootPath;
		static TArray< ImageInfo> _imageInfo;
		static bool _usePtagMaterialName;
	};
}
